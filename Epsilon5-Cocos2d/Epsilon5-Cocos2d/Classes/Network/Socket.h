#pragma once

#include <string>
#include <cstdint>

class Socket {
public:
    Socket();
    ~Socket();

    void connect(const std::string& host, std::uint16_t port);
    bool isConnected();
    void close();

    void write(void* buffer, int length);
    int read(void* buffer, int length);

private:
    int mSocket;
};
