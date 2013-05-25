#pragma once

#include <memory>
#include "uexception.h"

template<typename T>
class UMaybe
{
public:
    UMaybe() {}
    UMaybe(const T& value) {
        Value.reset(new T(value));
    }
    inline bool Has() {
        return Value;
    }
    inline T& operator *() {
        if (!Value) {
            throw UException("Value not initialized");
        }
    }
private:
    std::unique_ptr<T> Value;
};
