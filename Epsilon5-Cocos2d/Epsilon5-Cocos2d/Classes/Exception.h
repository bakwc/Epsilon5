#pragma once

#include <stdexcept>
#include <sstream>

#define check(expression, exception, ...) check_(expression, exception, ##__VA_ARGS__)
#define fail(exception, ...) check_(false, exception, ##__VA_ARGS__)

#define checkNotNull(pointer, ...) (check(pointer, std::invalid_argument, ##__VA_ARGS__), pointer)
#define checkArgument(expression, ...) check(expression, std::invalid_argument, ##__VA_ARGS__)
#define checkState(expression, ...) check(expression, std::domain_error, ##__VA_ARGS__)

#define check_(expression, exception, ...) \
    (!(expression) ? ExceptionImpl::throwException<exception>(\
        std::ostringstream(), #exception, __FILE__, __LINE__, ##__VA_ARGS__) : void())

class Exception : public std::runtime_error {
public:
    explicit Exception(const std::string& message) : std::runtime_error(message) {
        puts(message.c_str());
    }
};

inline void handleException(Exception& e) {
    puts("Unhandled exception.");
    std::terminate();
}

namespace ExceptionImpl {

    inline void prepareException(std::ostringstream& stream, const char* exception, const char* file, int line) {
        stream << exception << ": file " << file << ", line " << line;
    }

    template <typename Exception>
    inline void throwException(std::ostringstream& stream) {
        throw Exception(stream.str());
    }

    template <typename Exception>
    inline void throwException(std::ostringstream& stream, const char* exception, const char* file, int line) {
        prepareException(stream, exception, file, line);
        stream << ".";
        throwException<Exception>(stream);
    }

    template <typename Exception, typename T>
    inline void throwException(std::ostringstream& stream, const char* exception, const char* file, int line,
        const T& arg)
    {
        prepareException(stream, exception, file, line);
        stream << ", " << arg;
        throwException<Exception>(stream);
    }

    template <typename Exception, typename T1, typename T2>
    inline void throwException(std::ostringstream& stream, const char* exception, const char* file, int line,
        const T1& arg1, const T2& arg2, ...)
    {
        prepareException(stream, exception, file, line);
        stream << ", " << arg1 << ", " << arg2;
        throwException<Exception>(stream);
    }

}
