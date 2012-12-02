#pragma once

#include <QString>

#include "uexception.h"

template<typename T>
T FromString(const QString& str);

class UFromStringFormat {
public:
    UFromStringFormat(const QString& str)
        : Str(str)
    {
    }
    template <typename T>
    inline operator T() const {
        return FromString<T>(Str);
    }
private:
    const QString& Str;
};

inline UFromStringFormat FromString(const QString& str) {
    return UFromStringFormat(str);
}

//inline QString ToString(int number) {
//    return QString::number(number);
//}

//inline QString ToString(uint number) {
//    return QString::number(number);
//}

//inline QString ToString(float number) {
//    return QString::number(number);
//}

template<typename T>
QString ToString(const T& t) {
    return QString::number(t);
}

inline QString ToString(const QByteArray& byteArray) {
    return QString::fromUtf8(byteArray);
}
