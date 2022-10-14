#include <iostream>

using arithmeticFcn = int(*)(int, int);
//typedef int (*arithmeticFcn)(int, int); //or like this

int add(int a, int b){
    return a+b;
}

int substract(int a, int b){
    return a-b;
}
int multiply(int a, int b){
    return a*b;
}

int divide(int a, int b){
    if (a > 0)
        return a/b;
    else
        std::cout << "Division by 0\n";
        return 0;
}

 arithmeticFcn getArithmeticFcn(const char sign){
    switch (sign)
    {
        default:
        case '+': return add;
        case '-': return substract;
        case '*': return multiply;
        case '/': return divide;
    }
 }


int main(){

    int a{0}; int b{0};
    char sign = ' ';

    std::cout << "Enter two numbers: ";
    std::cin >> a >> b;
    std::cout << "Enter sign of operation (+, -, *, /): ";
    std::cin >> sign;

    arithmeticFcn fcn = getArithmeticFcn(sign);
    std::cout << fcn(a, b) << "\n";

    return 0;
}