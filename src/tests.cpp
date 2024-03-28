#include "../include/print.h"

#include <iostream>
#include <sstream>

int main()
{
    using namespace printable;

    println("{1} {0} ({})", " world!", "Hello");

    std::cout << format("{} || {}", 3.1415, 10000L) << '\n';
}