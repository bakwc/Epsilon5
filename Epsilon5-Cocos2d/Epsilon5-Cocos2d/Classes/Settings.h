#pragma once

#include <unordered_map>
#include <string>

#include "Util/Cast.h"
#include "Exception.h"

class KeyNotFountException : public Exception {
public:
    explicit KeyNotFountException(const std::string& message) : Exception(message) {
    }
};


class Settings
{
public:
    Settings();
    ~Settings();

    const std::string& getString(const std::string& key) const;
    StringConverter get(const std::string& key) const;

private:
    std::unordered_map<std::string, std::string> mValues;
};
