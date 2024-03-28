#pragma once

#include "format.h"
#include <iostream>

namespace printable {

inline void print(const std::string& str)
{
    std::cout << str;
}

template <typename... FormatableTypes>
inline void print(const std::string& formatStr, FormatableTypes... formatables)
{
    std::cout << format(formatStr, formatables...);
}

template <typename... FormatableTypes>
inline void println(const std::string& formatStr, FormatableTypes... formatables)
{
    print(formatStr, formatables...);
    std::cout << '\n';
}

inline void println(const std::string& formatStr)
{
    print(formatStr);
    std::cout << '\n';
}
} // namespace printable