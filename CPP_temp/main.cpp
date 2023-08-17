#include <iostream>
#include <numbers> 
#include <format>
#include <vector>

int main(){

    srand(static_cast<unsigned int>(time(0)));
    //system("cls");
    
    std::vector vec = {0,2,4,5,2,3,4,5,5,6};
    std::cout << "vec.size() = " << vec.size() << "\n";
    for(auto& move : vec){
        
        move = rand() % vec.size();
        std::cout << move << "\n";

    }

    return 0;

}