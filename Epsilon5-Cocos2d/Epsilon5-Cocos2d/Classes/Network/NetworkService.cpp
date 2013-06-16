#include "NetworkService.h"

#include "zlib/zlib.h"

#include "NetworkException.h"
#include "MessageProcessor.h"

namespace {

    inline bool isHostBigEndian() {
        return (bool) (*(unsigned short *) "\0\xff" < 0x100);
    }

    void correctByteOrder(void* data, int size, bool isBigEndian) {
        if (isHostBigEndian() != isBigEndian) {
            char* b = static_cast<char*>(data);
            for (int i = 0; i < --size; ++i) {
                const char temp = b[i];
                b[i] = b[size];
                b[size] = temp;
            }
        }
    }

    template <typename T>
    T correctByteOrder(T value, bool isBigEndian) {
        correctByteOrder(&value, sizeof(value), isBigEndian);
        return value;
    }
}

NetworkService::NetworkService(std::shared_ptr<MessageProcessor> processor)
    : mProcessor(checkNotNull(processor))
{
}

NetworkService::~NetworkService() {
    checkState(!mIsConnected);
}

void NetworkService::connect(const std::string& host, int port) {
    mSocket.connect(host, port);
    mIsConnected = true;
    mThread.reset(new std::thread(std::bind(&NetworkService::run, this)));
}

void NetworkService::close() {
    if (mIsConnected) {
        mIsConnected = false;
        mSocket.close();
        mThread->join();
        mThread.reset();
    }
}

void NetworkService::send(PacketType type, const google::protobuf::Message& message) {
    const int rawSize = message.ByteSize();
    updateBufferSize(mRawBuffer, rawSize, false);
    const bool serialized = message.SerializeToArray(mRawBuffer.data(), rawSize);
    checkNetwork(serialized);

    unsigned long compressedSize = compressBound(rawSize);
    updateBufferSize(mNetBuffer, compressedSize + HEADER_SIZE, false);
    const int compressed = compress(mNetBuffer.data() + HEADER_SIZE, &compressedSize,
        mRawBuffer.data(), rawSize);
    checkNetwork(compressed == Z_OK, compressed);

    write<std::uint8_t>(mNetBuffer, 0, static_cast<int>(type));
    write<std::uint16_t>(mNetBuffer, 1, rawSize);
    write<std::uint16_t>(mNetBuffer, 3, compressedSize + 4);
    write<std::uint32_t>(mNetBuffer, 5, compressedSize);

    mSocket.write(mNetBuffer.data(), compressedSize + HEADER_SIZE);
}

void NetworkService::updateBufferSize(Buffer& buffer, int size, bool copy) {
    if (static_cast<int>(buffer.size()) < size) {
        if (!copy) {
            buffer.resize(0);
        }
        buffer.resize(size + BUFFER_RESERVE_SIZE);
    }
}

template <typename T>
inline T& NetworkService::getRawVariable(Buffer& buffer, int shift) {
    return *reinterpret_cast<T*>(buffer.data() + shift);
}

template <typename T>
inline T NetworkService::read(Buffer& buffer, int shift) {
    return correctByteOrder(getRawVariable<T>(buffer, shift), true);
}

template <typename T>
void NetworkService::write(Buffer& buffer, int shift, T value) {
    getRawVariable<T>(buffer, shift) = correctByteOrder(value, true);
}

void NetworkService::run()
try {
    Buffer netBuffer(BUFFER_RESERVE_SIZE);
    Buffer rawBuffer;

    int shift = 0;
    bool isHeader = true;
    PacketType packetType;
    int compressedSize;

    while (mIsConnected) {
        updateBufferSize(netBuffer, shift, true);

        int bytesRead = shift + mSocket.read(netBuffer.data() + shift, netBuffer.size() - shift);
        shift = bytesRead;

        if (isHeader) {
            if (bytesRead >= HEADER_SIZE) {
                isHeader = false;
                packetType = static_cast<PacketType>(read<std::uint8_t>(netBuffer, 0));
                const int rawSize = read<std::uint16_t>(netBuffer, 1);
                compressedSize = read<std::uint16_t>(netBuffer, 3) - 4;
                updateBufferSize(netBuffer, compressedSize, true);
                updateBufferSize(rawBuffer, rawSize, false);
            } else {
                continue;
            }
        }

        const int packetSize = HEADER_SIZE + compressedSize;
        if (!isHeader && bytesRead >= packetSize) {
            unsigned long rawSize = rawBuffer.size();
            const int uncompressed = uncompress(rawBuffer.data(), &rawSize,
                netBuffer.data() + HEADER_SIZE, compressedSize);
            checkNetwork(uncompressed == Z_OK, uncompressed);

            mProcessor->process(packetType, rawBuffer.data(), rawSize);

            std::copy(netBuffer.begin() + packetSize, netBuffer.begin() + bytesRead, netBuffer.begin());
            isHeader = true;
            shift = bytesRead - packetSize;
        }
    }
} catch (Exception& e) {
    handleException(e);
}
