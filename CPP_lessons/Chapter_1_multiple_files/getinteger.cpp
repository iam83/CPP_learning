#include "iostream"

int getInteger() // определение функции
{
    std::cout << "Enter an integer: ";
    int x;
    std::cin >> x;
    return x;
}
