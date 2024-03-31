#pragma once

#include "FormatOptions.hpp"
#include "Formatter.hpp"
#include <string>

namespace printable {

namespace detail {
template <template <typename T, typename Alloc> class Container, typename T, typename Alloc>
std::string container_format_helper(const Container<T, Alloc>& from, char)
{
    static_assert(false, "Unimplemented!");
    return "";
}
}; // namespace detail

template <>
class Formatter<bool>
{
public:
    static std::string format(bool from, const FormatOptions& options)
    {
        std::string result;
        if (from) {
            result = "true";
        } else {
            result = "false";
        }

        result = options.pad(result);

        return result;
    }
};

#ifdef __cpp_lib_span
#include <span>

template <typename T>
class Formatter<std::span<T>>
{
public:
    static std::string format(const std::span<T>& from, const FormatOptions& options)
    {
        std::stringstream ss;
        std::string result;

        ss << '[';
        for (const auto& elem : from) {
            ss << Formatter<T>::format(elem, {{}}); // TODO: Enable some options?
            ss << ',';
        }

        // Overwrite final ',' character
        ss.seekp(-1, std::ios::end) << ']';

        result = ss.str();
        result = options.pad(result);

        return result;
    }
};
#endif

template <template <typename T, typename Alloc> class Container, typename T, typename Alloc>
class Formatter<Container<T, Alloc>>
{
public:
    static std::string format(const Container<T, Alloc>& from, const FormatOptions& options)
    {
#ifdef __cpp_lib_span
        return Formatter<std::span<T>>::format(from, options);
#else
        std::stringstream ss;
        std::string result;

        ss << '[';
        for (const auto& elem : from) {
            ss << Formatter<T>::format(elem, {{}}); // TODO: Enable some options?
            ss << ',';
        }

        // Overwrite final ',' character
        ss.seekp(-1, std::ios::end) << ']';

        result = ss.str();
        result = options.pad(result);

        return result;
#endif
    }
};

template <typename T1, typename T2>
class Formatter<std::pair<T1, T2>>
{
public:
    static std::string format(const std::pair<T1, T2>& from, const FormatOptions& options)
    {
        std::stringstream ss;
        std::string result;

        ss << '(';

        ss << Formatter<T1>::format(from.first, {{}}); // TODO: Enable some options?
        ss << ',';
        ss << Formatter<T2>::format(from.second, {{}}); // TODO: Enable some options?
        // Overwrite final ',' character
        ss << ')';

        result = ss.str();
        result = options.pad(result);

        return result;
    }
};

// template <typename T>
// class Formatter<std::vector<T>>
// {
// public:
// };

} // namespace printable