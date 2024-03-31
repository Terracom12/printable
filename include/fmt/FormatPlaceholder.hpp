#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

namespace printable {

// FIXME: Using Rust idioms. Not ideal for C++. Constructor?
class FormatPlaceholder
{
private:
    FormatPlaceholder() = default;

public:
    static FormatPlaceholder parse(std::string optionsStr);

    const bool isDebug = false;
    const bool isPrettyPrint = false;
    const enum class Direction { NONE = 0, LEFT = '<', RIGHT = '>', CENTER = '^' } alignment = Direction::NONE;
    const std::size_t padding = 0;
    const char paddingChar = ' ';

    const std::size_t position = 0;
};

inline FormatPlaceholder FormatPlaceholder::parse(std::string optionsStr)
{
    // TODO: Finish this
    // TODO: Write tests
    // Based on the rust format spec: https://doc.rust-lang.org/std/fmt/#syntax

    if (optionsStr.empty()) {
        return {};
    }

    bool isDebug = false;
    bool isPrettyPrint = false;
    Direction alignment = Direction::NONE;
    std::size_t padding = 0;
    char paddingChar = ' ';
    std::size_t position = 0;

    // TODO: Even more exception handling
    // TODO: Custom format exception

    // Parse the argument number if it exists
    try {
        std::size_t nextPos = 0;
        std::size_t argumentNum = std::stoi(optionsStr, &nextPos);
        position = argumentNum;
        optionsStr.erase(0, nextPos);
    } catch (const std::invalid_argument&) {
        // TODO
    } catch (const std::out_of_range&) {
        throw;
    }

    if (optionsStr.empty()) {
        return {isDebug, isPrettyPrint, alignment, padding, paddingChar, position};
    }

    if (optionsStr[0] == ':') {
        optionsStr.erase(0, 1);
    }

    if (optionsStr.empty()) {
        return {isDebug, isPrettyPrint, alignment, padding, paddingChar, position};
    }

    if (optionsStr[0] != '<' && optionsStr[0] != '^' && optionsStr[0] != '>') {
        paddingChar = optionsStr[0];
        optionsStr.erase(0, 1);
    }

    try {

    } catch (...) {
    }
    switch (optionsStr[0]) {
    case '<':
        alignment = Direction::LEFT;
        optionsStr.erase(0, 1);
        break;
    case '^':
        alignment = Direction::CENTER;
        optionsStr.erase(0, 1);
        break;
    case '>':
        alignment = Direction::RIGHT;
        optionsStr.erase(0, 1);
        break;
    }

    return {isDebug, isPrettyPrint, alignment, padding, paddingChar, position};
}

} // namespace printable