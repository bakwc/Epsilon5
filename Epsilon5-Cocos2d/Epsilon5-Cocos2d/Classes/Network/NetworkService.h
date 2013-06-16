#pragma once

#include <vector>
#include <memory>
#include <atomic>
#include <thread>

#include <google/protobuf/message.h>

#include "PacketType.h"
#include "Socket.h"

class MessageProcessor;

class NetworkService {
public:
    NetworkService(std::shared_ptr<MessageProcessor> processor);
    ~NetworkService();

    void connect(const std::string& host, int port);
    void close();

    void send(PacketType type, const google::protobuf::Message& message);

private:
    typedef std::vector<std::uint8_t> Buffer;

    enum {
        BUFFER_RESERVE_SIZE = 1024,
        HEADER_SIZE = 9,
    };

private:
    const std::shared_ptr<MessageProcessor> mProcessor;
    Socket mSocket;
    Buffer mRawBuffer;
    Buffer mNetBuffer;
    std::unique_ptr<std::thread> mThread;
    std::atomic_bool mIsConnected;

private:
    void run();
    void updateBufferSize(Buffer& buffer, int size, bool copy);

    template <typename T>
    static T& getRawVariable(Buffer& buffer, int shift);

    template <typename T>
    static T read(Buffer& buffer, int shift);

    template <typename T>
    static void write(Buffer& buffer, int shift, T value);
};
