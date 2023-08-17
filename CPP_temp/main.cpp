#include <iostream>
#include <numbers> 
#include <format>
#include <vector>


int main(){

    //srand(static_cast<unsigned int>(time(0)));
    system("clear");
    
    std::vector<std::string> vec{};

    std::string row = "ABCDEFGHIJ";


    for (int i = 0; i <= 9; ++i) {
        for (int j = 0; j <= 9; ++j) {
            vec.push_back(row[i] + std::to_string(j));
        }
    }

    for(size_t count{0}; count < vec.size(); ++count){
        std::cout << vec[count] << " ";
        if ((count+1) % 10 == 0)
            std::cout << std::endl;

    }

    std::cout << std::endl;
    std::cout << std::endl;

    for(size_t i{}; i<100; ++i){
        std::cout << i << " ";
        if ((i+1) % 10 == 0)
            std::cout << std::endl;

    }

    

    return 0;

}