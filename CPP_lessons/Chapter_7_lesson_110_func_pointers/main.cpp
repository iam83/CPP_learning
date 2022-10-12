#include <iostream>

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

 int getArithmeticFcn(const char sign){
    
 }

using arithmeticFcn = int(*)(int, int);

int main(){

    int a{0}; int b{0};
    char sign = ' ';

    std::cout << "Enter two numbers: ";
    std::cin >> a >> b;
    std::cout << "Enter sign of operation (+, -, *, /): ";
    std::cin >> sign;


    return 0;
}