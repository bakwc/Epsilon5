#pragma once

#include "Exception.h"

#define checkNetwork(expression, ...) check(expression, NetworkException, ##__VA_ARGS__)

class NetworkException : public Exception {
public:
    explicit NetworkException(const std::string& message) : Exception(message) {
    }
};
