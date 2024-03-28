#include "../include/print.h"

#include <iostream>
#include <sstream>

int main()
{
    using namespace printable;
    std::stringstream ss;
    ss << 1.214;

    std::cout << "Hello World!\n";

    println("{1} {0} ({}) {}", " world!", "Hello");
}