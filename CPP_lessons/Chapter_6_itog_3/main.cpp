/*

            Задание No3
        Напишите свою функцию, которая меняет местами значения двух целочисленных переменных.
        Проверку осуществляйте в функции main().
        Подсказка: Используйте ссылки в качестве параметров.

*/

#include <iostream>

void swapValues(int &a, int &b){
    int temp = 0;
    temp = a;
    a = b;
    b = temp;
}

int main(){

    int a = 10;
    int b = 20;

    std::cout << "Before: a = " << a << " and b = " << b << std::endl;

    swapValues(a, b);

    std::cout << "After: a = " << a << " and b = " << b << std::endl;

    return 0;
}