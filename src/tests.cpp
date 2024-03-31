#include "../include/print.hpp"

#include <iostream>
#include <vector>

int main()
{
    using namespace printable;
    struct A
    {
    };
    FormatOptions ops{{false, false, FormatPlaceholder::Direction::RIGHT, 10}};
    std::vector<std::pair<bool, float>> v = {{false, 3.1415}, {true, 100.999}};
    std::cout << format("{1} {}\n", v, "Hi: ");

    // println("{1} {0} ({2})", " world!", "Hello", 3.1425);

    // std::cout << format("{} || {}\n", 3.1415, 10000L);
}