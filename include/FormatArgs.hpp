#pragma once


#include <cstddef>

namespace printable {

template <typename... FormatableTypes>
class FormatArgs
{
public:
    FormatArgs(FormatableTypes... formatables) {}

    constexpr std::size_t size() const
    {
        return sizeof...(FormatableTypes);
    }
};
} // namespace printable