#include <iostream>
#include <array>

using arithmeticFcn = int(*)(int, int);
//typedef int (*arithmeticFcn)(int, int); //or like this

struct arithmeticStruct {
    char op;
    arithmeticFcn fcn;
};

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

 arithmeticFcn getArithmeticFcn(const std::array<arithmeticStruct, 4> & arr, char & sign){
    for (const auto& a : arr){
        if (a.op == sign) return a.fcn;
    }
 }


int main(){

    int a{0}; int b{0};
    char sign = ' ';
    std::array<arithmeticStruct, 4> arithmeticArray = {{{'+', add}, {'-', substract},
                                                   {'*', multiply}, {'/', divide}}};

    std::cout << "Enter two numbers: ";
    std::cin >> a >> b;
    std::cout << "Enter sign of operation (+, -, *, /): ";
    std::cin >> sign;

    arithmeticFcn fcn = getArithmeticFcn(arithmeticArray, sign);
    std::cout << fcn(a, b) << "\n";

    return 0;
}