#pragma once

#include "FormatString.h"
#include "format.h"
#include "util.h"

#include <atomic>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

namespace printable {

template <typename T>
class Formatable
{
public:
    Formatable() = delete;

    constexpr Formatable(const T& data, FormatOptions options = {})
        : data(data)
        , options(options)
    {}

    constexpr void changeOptions(FormatOptions options)
    {
        this->options = options;
    };

    std::string format() const
    {
        std::string result = formatSpecific();
        return options.formatted(result);
    };
    std::enable_if_t<true, std::string> formatSpecific() const
    {
        std::stringstream ss;
        ss << data;
        return ss.str();
    }

    constexpr size_t getArgNum() const
    {
        return options.argumentNumber;
    }

private:
    const T& data;
    FormatOptions options;
};

template <typename... FormatableTypes>
class FormatArgs
{
public:
    using Types = util::heterogeneous_variant_t<std::variant<Formatable<FormatableTypes>...>>;
    FormatArgs(Formatable<FormatableTypes>... formatables)
        : data{Types{formatables}...}
    {}

    constexpr std::size_t size() const
    {
        return sizeof...(FormatableTypes);
    }

    std::string get(size_t index) const
    {
        // TODO: This can be made better
        if (index >= size()) {
            throw std::out_of_range("Error! Index is out of bounds!");
        }

        return std::visit([](auto&& item) { return item.format(); }, data[index]);
    }

    void changeOptions(size_t index, FormatOptions options)
    {
        // TODO: This can be made better
        if (index >= size()) {
            throw std::out_of_range("Error! Index is out of bounds!");
        }

        std::visit([&options](auto&& item) { item.changeOptions(options); }, data[index]);
    }

private:
    std::vector<Types> data;
};
} // namespace printable