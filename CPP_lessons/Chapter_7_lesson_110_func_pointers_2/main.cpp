#include <iostream>
#include <array>

using arithmeticFcn = double(*)(double, double);
//typedef int (*arithmeticFcn)(int, int); //or like this

struct arithmeticStruct {
    char op;
    arithmeticFcn fcn;
};

double add(double a, double b){
    return a+b;
}

double substract(double a, double b){
    return a-b;
}
double multiply(double a, double b){
    return a*b;
}

double divide(double a, double b){
    if (b > 0)
        return a/b;
    else
        std::cout << "Error. Division by 0\n";
        return 0;
}

 arithmeticFcn getArithmeticFcn(const std::array<arithmeticStruct, 4> & arr, char & sign){
    for (const auto& a : arr){
        if (a.op == sign) return a.fcn;
    }
 }


int main(){

    double a{0}; double b{0};
    char sign = ' ';
    std::array<arithmeticStruct, 4> arithmeticArray = { {{'+', add},
                                                         {'-', substract},
                                                         {'*', multiply},
                                                         {'/', divide}} };

    std::cout << "Enter two numbers: ";
    std::cin >> a >> b;
    std::cout << "Enter sign of operation (+, -, *, /): ";
    std::cin >> sign;

    arithmeticFcn fcn = getArithmeticFcn(arithmeticArray, sign);
    std::cout << fcn(a, b) << "\n";

    return 0;
}