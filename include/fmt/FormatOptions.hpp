#pragma once

#include "FormatPlaceholder.hpp"

namespace printable {

class FormatOptions : protected FormatPlaceholder
{
public:
    FormatOptions(const FormatPlaceholder& placeholder)
        : FormatPlaceholder{placeholder}
    {}
    std::string pad(const std::string& str) const;

    constexpr size_t getPosition() const
    {
        return position;
    }

    bool operator<(const FormatOptions& rhs)
    {
        return position < rhs.position;
    }
};

inline std::string FormatOptions::pad(const std::string& str) const
{
    ssize_t paddingAmt = padding - str.size();

    if (paddingAmt <= 0) {
        return str;
    }

    switch (alignment) {
    case Direction::LEFT:
        return str + std::string(paddingAmt, paddingChar);
    case Direction::RIGHT:
        return std::string(paddingAmt, paddingChar) + str;
    case Direction::CENTER:
        // FIXME: Invalid result if paddingAmt is odd
        return std::string(paddingAmt / 2, paddingChar) + str + std::string(paddingAmt / 2, paddingChar);
    case Direction::NONE:
        return str;
    }
}

} // namespace printable