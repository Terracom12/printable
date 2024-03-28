#pragma once

#include <stdexcept>
#include <string>

namespace printable {

// FIXME: Using Rust idioms. Not ideal for C++.
struct FormatPlaceholder
{
private:
    FormatPlaceholder();

public:
    static FormatPlaceholder parse(std::string optionsStr);

protected:
    bool isDebug = false;
    bool prettyPrint = false;
    enum class NumericMode { BINARY, OCTAL, DECIMAL, HEX, NONE } encodingMode = NumericMode::NONE;
    enum class Direction { LEFT = '<', RIGHT = '>', CENTER = '^' } padDirection = Direction::RIGHT;
    std::size_t padding = 0;
    char paddingChar = ' ';
    std::size_t position = 0;
};

inline FormatPlaceholder FormatPlaceholder::parse(std::string optionsStr)
{
    // TODO: Finish this
    // TODO: Write tests
    // Based on the rust format spec: https://doc.rust-lang.org/std/fmt/#syntax

    if (optionsStr.empty()) {
        return {};
    }

    FormatPlaceholder options{};

    // TODO: Even more exception handling
    // TODO: Custom format exception

    // Parse the argument number if it exists
    try {
        std::size_t nextPos = 0;
        std::size_t argumentNum = std::stoi(optionsStr, &nextPos);
        options.position = argumentNum;
        optionsStr.erase(0, nextPos);
    } catch (const std::invalid_argument&) {
        // TODO
    } catch (const std::out_of_range&) {
        throw;
    }

    if (optionsStr.empty()) {
        return options;
    }

    if (optionsStr[0] == ':') {
        optionsStr.erase(0, 1);
    }

    if (optionsStr.empty()) {
        return options;
    }

    if (optionsStr[0] != '<' && optionsStr[0] != '^' && optionsStr[0] != '>') {
        options.paddingChar = optionsStr[0];
        optionsStr.erase(0, 1);
    }

    try {

    } catch (...) {
    }
    switch (optionsStr[0]) {
    case '<':
        options.padDirection = Direction::LEFT;
        optionsStr.erase(0, 1);
        break;
    case '^':
        options.padDirection = Direction::CENTER;
        optionsStr.erase(0, 1);
        break;
    case '>':
        options.padDirection = Direction::RIGHT;
        optionsStr.erase(0, 1);
        break;
    }

    return options;
}

inline std::string FormatOptions::formatted(std::string str) const
{
    return pad(str);
}

inline std::string FormatOptions::pad(std::string str) const
{
    ssize_t padDiff = padding - str.size();

    if (padDiff <= 0) {
        return str;
    }

    switch (padDirection) {
    case Direction::LEFT:
        return str + std::string(padDiff, paddingChar);
    case Direction::RIGHT:
        return std::string(padDiff, paddingChar) + str;
    case Direction::CENTER:
    default:
        [[unreachable]]
    }
}

} // namespace printable