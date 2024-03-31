#pragma once

#include "FormatOptions.hpp"
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>

namespace printable {

template <typename T>
class Formatter
{
public:
    // Default behavior: use std::ostream operator<< if it's implemented

    template <typename Ty = T,
              std::enable_if_t<std::is_same_v<decltype(std::cout << std::declval<Ty>()), std::ostream&>, bool> = true>
    static std::string format(const T& from, const FormatOptions& options)
    {
        std::stringstream ss;
        ss << from;
        std::string result = ss.str();

        result = options.pad(result);

        return result;
    }
};

} // namespace printable

#include "FormatterImpls.hpp"