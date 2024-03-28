#pragma once

#include "FormatArgs.h"

#include <iostream>
#include <regex>
#include <sstream>
#include <string>

namespace printable {

template <typename... FormatableTypes>
inline std::string format(const std::string& formatStr, FormatableTypes... formatables)
{
    std::string result{};
    FormatArgs fmt = FormatArgs(Formatable<FormatableTypes>{formatables}...);

    // TODO: Extract into function
    std::regex fmtRegex("\\{(.*?)\\}");
    int i = 0;
    // Based on the algorithm of regex_replace described at: https://en.cppreference.com/w/cpp/regex/regex_replace
    std::sregex_iterator last_match;
    for (auto match = std::sregex_iterator(formatStr.begin(), formatStr.end(), fmtRegex);
         match != std::sregex_iterator(); ++match) {

        std::string matchInnards = (*match)[1].str();
        if (matchInnards.size() == 1) {
            if (matchInnards >= "0" && matchInnards <= "9") {
                i = *matchInnards.c_str() - '0';
            }
        }
        result += match->prefix();
        result += fmt.get(i); // TODO
        ++i;
        last_match = match;
    }
    result += last_match->suffix();

    return result;
}
}; // namespace printable