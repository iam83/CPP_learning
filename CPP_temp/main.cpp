#include <iostream>
#include <numbers> 
#include <format>

int main(){

    //system("cls");

    int temp {5};
    std::cout << std::numbers::phi << "\n";
    std::cout << std::format("Month {:>3}: {:>10}  |  profit per month: {:>10.2f}", temp, 30000000, 20000.2555453);
    std::cout << std::endl;
    //std::cout << std::format("Month {:>3}: {:>10}  |  profit per month: {:>10.2f}", 20, 1000000, 200000.02456535);
    std::cout << std::endl;
    std::cout << std::endl;

    //setlocale(LC_ALL, "Russian");
    //int temp {4096};
    //std::cout << (temp << 2);
    //std::cout << std::endl;

    //std::cout << std::locale().name() << std::endl;
    //std::locale::global(std::locale(""));
    //std::cout << "\033[32mThis is green\033[0m" << std::endl;
    return 0;

}