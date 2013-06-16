#include "Socket.h"

#include <sstream>

#include "NetworkException.h"

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <WinSock2.h>

#else
#include <sys/socket.h>
#include <unistd.h>
#endif

#define checkSocket(expression, ...) checkNetwork(expression, getSocketError(), ##__VA_ARGS__)

namespace {

    inline int getSocketError() {
#ifdef _WIN32
        return WSAGetLastError();
#else
        return errno();
#endif
    }

}

Socket::Socket() : mSocket(INVALID_SOCKET) {
#ifdef _WIN32
    WSAData data;
    std::memset(&data, 0, sizeof(data));
    const int res = WSAStartup(MAKEWORD(2, 2), &data);
    checkSocket(res == 0);
#endif
}

Socket::~Socket() {
    checkState(!isConnected());

#ifdef _WIN32
    WSACleanup();
#endif
}

void Socket::connect(const std::string& host, std::uint16_t port) {
    checkState(!isConnected());

    mSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    checkSocket(mSocket != INVALID_SOCKET);

    try {
        sockaddr_in addr;
        std::memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(host.c_str());
        addr.sin_port = htons(port);

        const int res = ::connect(mSocket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
        checkSocket(res != SOCKET_ERROR);
    } catch (...) {
        close();
        throw;
    }
}

bool Socket::isConnected() {
    return mSocket != INVALID_SOCKET;
}

void Socket::close() {
    if (mSocket != INVALID_SOCKET) {
#ifdef _WIN32
        const int res = closesocket(mSocket);
#else
        const int res = ::close(mSocket);
#endif
        mSocket = INVALID_SOCKET;
        checkSocket(res != SOCKET_ERROR);
    }
}

void Socket::write(void* buffer, int length) {
    const int bytesSent = send(mSocket, static_cast<char*>(buffer), length, 0);
    checkSocket(bytesSent == length);
}

int Socket::read(void* buffer, int length) {
    const int bytesRead = recv(mSocket, static_cast<char*>(buffer), length, 0);
    if (bytesRead == SOCKET_ERROR) {
#ifdef _WIN32
        if (getSocketError() == WSAEINTR) {
#else
        if (getSocketError() == EINTR) {
#endif
            return 0;
        }
    }
    checkSocket(bytesRead != SOCKET_ERROR);
    return bytesRead;
}
