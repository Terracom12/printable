#pragma once

#include <type_traits>
#include <variant>

namespace printable {

#ifndef __cpp_lib_logical_traits
// Based off implementation at: https://en.cppreference.com/w/cpp/types/disjunction
template <typename...>
struct disjunction : std::false_type
{
};
template <typename B1>
struct disjunction<B1> : B1
{
};
template <typename B1, typename... Bn>
struct disjunction<B1, Bn...> : std::conditional_t<bool(B1::value), B1, disjunction<Bn...>>
{
};
#else
using std::disjunction;
#endif

// Implementation based off of: https://stackoverflow.com/a/62089731
// TODO: Figure out how the hell this works

// end of recursive call: tuple is forwared using `type`
template <typename T, typename... Ts>
struct unique_impl
{
    using type = T;
};

// recursive call: 1. Consumes the first type of the variadic arguments,
//                    if not repeated add it to the tuple.
//                 2. Call this again with the rest of arguments
template <template <class...> class Tuple, typename... Ts, typename U, typename... Us>
struct unique_impl<Tuple<Ts...>, U, Us...>
    : std::conditional_t<disjunction<std::is_same<U, Ts>...>::value, unique_impl<Tuple<Ts...>, Us...>,
                         unique_impl<Tuple<Ts..., U>, Us...>>
{
};

template <typename Variant>
struct heterogeneous_variant
{
};

template <template <class...> class Variant, typename... Ts>
struct heterogeneous_variant<Variant<Ts...>> : unique_impl<Variant<>, Ts...>
{
};

template <class Variant>
using heterogeneous_variant_t = typename heterogeneous_variant<Variant>::type;
} // namespace printable