#include <iostream>

int getInteger(); // предварительное объявление с использованием прототипа функции

int main()
{
    int x = getInteger();
    int y = getInteger();
 
    std::cout << x << " + " << y << " is " << x + y << '\n';
    return 0;
}
