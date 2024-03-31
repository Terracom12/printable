# Printable

My own (rather inadequate) header-only implementation of `std::format` and `std::print` for pre-C++17. Naively uses `std::ostream` for backend functionality.

## Grammar

Heavily inspired by Rust's [`fmt`](https://doc.rust-lang.org/std/fmt/).

```text
format_string ::= text [ maybe_format text ] *
maybe_format ::= '{' '{' | '}' '}' | format
format ::= '{' [ argument ] [ ':' format_spec ] '}'
argument ::= uint

format_spec ::= [[fill] align] ['+'] ['#'] [width] ['.' precision] [type]
fill ::= character
align ::= '<' | '^' | '>'
width ::= uint
precision ::= uint
type ::= '' | '?'

text ::= [character - '{' | '}'] *
uint ::= [0-9] +
```
