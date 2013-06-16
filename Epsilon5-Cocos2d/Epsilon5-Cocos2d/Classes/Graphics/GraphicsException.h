#pragma once

#include "Exception.h"

#define checkGraphics(expression, ...) check(expression, GraphicsException, ##__VA_ARGS__)

class GraphicsException : public Exception {
public:
    explicit GraphicsException(const std::string& message) : Exception(message) {
    }
};
