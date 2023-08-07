#include <iostream>
#include <numbers> 
#include <format>

int main(){
    int temp {5};
    std::cout << std::numbers::phi << "\n";
    std::cout << std::format("Hello {}", temp);
    return 0;
    
}