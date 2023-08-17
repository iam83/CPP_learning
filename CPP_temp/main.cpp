#include <iostream>
#include <numbers> 
#include <format>
#include <vector>

int main(){

    //system("cls");

    // char temp_first[] = "ABCDEFGHIJ"; 
    // char temp_second[] = "0123456789";
    std::string joined = "";
    std::string temp_first = "ABCDEFGHIJ";
    std::string temp_second = "0123456789";
    std::vector<std::string> moves{};

    for (size_t row{}, count{}; row < 10; ++row){
        for(size_t col{}; col < 10; ++col){
                joined += temp_first[col];
                joined += temp_second[row];
                moves.push_back(joined);
                std::cout << joined << " ";
                joined = "";
                if (!((++count) % 10))
                    std::cout << std::endl;

        }
        
    }

    for(const auto& move : moves){
        
        std::cout << move << " ";

    }

    return 0;

}