#pragma once

#include <string>
#include <cstdint>

class StringConverter {
public:
    explicit StringConverter(const std::string& str);

    template <typename T>
    operator T() const;

private:
    const std::string& mStr;
};

inline StringConverter fromString(const std::string& str) {
    return StringConverter(str);
}

inline StringConverter::StringConverter(const std::string& str)
    : mStr(str)
{
}

template <>
inline StringConverter::operator std::string() const {
    return mStr;
}

template <>
inline StringConverter::operator const char*() const {
    return mStr.c_str();
}

template <>
inline StringConverter::operator int() const {
    return std::stoi(mStr);
}

template <>
inline StringConverter::operator std::uint16_t() const {
    return std::stoi(mStr);
}
