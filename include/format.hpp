#pragma once

#include "fmt/FormatOptions.hpp"
#include "fmt/FormatPlaceholder.hpp"
#include "fmt/Formatter.hpp"

#include <algorithm>
#include <iterator>
#include <list>
#include <numeric>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

namespace printable {

namespace detail {

inline void format_helper(std::vector<std::string>& result, size_t currentPosition,
                          const std::vector<FormatOptions>& options)
{}

template <typename FormatableType, typename... FormatableTypes>
inline void format_helper(std::vector<std::string>& result, size_t currentPosition,
                          const std::vector<FormatOptions>& options, FormatableType formatable,
                          FormatableTypes... formatables)
{
    if (result.empty()) {
        result.resize(options.size());
    }

    // TODO: Compile-time errors
    if (options.size() < 1) {
        throw std::logic_error("More arguments provided than format placeholders!");
    }

    auto currentOpt = options.begin();
    while ((currentOpt = std::find_if(currentOpt, options.end(), [&currentPosition](const auto& elem) {
                return elem.getPosition() == currentPosition;
            })) != options.end()) {
        size_t i = std::distance(options.begin(), currentOpt);
        result[i] = Formatter<FormatableType>::format(formatable, *currentOpt);
        ++currentOpt;
    }

    format_helper(result, currentPosition + 1, options, formatables...);
}

} // namespace detail

template <typename... FormatableTypes>
inline std::string format(const std::string& formatStr, FormatableTypes... formatables)
{
    std::vector<std::string> resultTokens{};
    std::vector<FormatOptions> options{};

    // TODO: Extract into function
    std::regex fmtRegex("\\{(.*?)\\}");
    // Based on the algorithm of regex_replace described at: https://en.cppreference.com/w/cpp/regex/regex_replace
    std::sregex_iterator last_match;
    for (auto match = std::sregex_iterator(formatStr.begin(), formatStr.end(), fmtRegex);
         match != std::sregex_iterator(); ++match) {

        std::string matchInnards = (*match)[1].str();
        resultTokens.push_back(match->prefix());
        options.emplace_back(FormatPlaceholder::parse(matchInnards));
        last_match = match;
    }
    resultTokens.push_back(last_match->suffix());

    std::vector<std::string> formattedTokens{};
    detail::format_helper(formattedTokens, 0, options, formatables...);

    // FIXME: There's probably an stl algorithm for this.
    for (auto i = resultTokens.begin(), j = formattedTokens.begin(); j != formattedTokens.end(); ++i, ++j) {
        resultTokens.insert(i + 1, *j);
    }
    return std::accumulate(resultTokens.cbegin(), resultTokens.cend(), std::string{});
}

}; // namespace printable