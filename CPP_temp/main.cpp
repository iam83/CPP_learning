#include <iostream>
#include <numbers>
#include <format>

int main(){

    std::cout << std::numbers::phi << "\n";
    std::cout << std::format("Hello {}", 10);
    return 0;
}