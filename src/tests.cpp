#include "../include/print.h"

#include <iostream>

int main()
{
    using namespace printable;

    println("{1} {0} ({2})", " world!", "Hello", 3.1425);

    std::cout << format("{} || {}\n", 3.1415, 10000L);
}