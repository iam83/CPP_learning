#include <iostream>
#include <array>
#include <ctime>

void printTwoFields(std::array<std::array<int, 10>, 10> const &field_pc, std::array<std::array<int, 10>, 10> const &field_user){

    std::string letters = "ABCDEFGHIJ";
    std::string separator = "          ";
    std::cout << "   ";

    for (auto const &lett : letters){
        std::cout << lett << " ";
    }

    std::cout << separator + "   ";

    for (auto const &lett : letters){
        std::cout << lett << " ";
    }

    std::cout << std::endl;

    for (int row = 0; row < field_pc.size(); ++row){
        std::cout << row << "  "; //row number
        
        for (int col = 0; col < field_pc.size(); ++col){// user field
            std::cout << field_user.at(row).at(col) << " ";
        }

        std::cout << separator;
        std::cout << row << "  ";

        for (int col = 0; col < field_pc.size(); ++col){ // pc field
            std::cout << field_pc.at(row).at(col) << " ";
        }
        
        std::cout << std::endl;

        }
}

void fillField(std::array<std::array<int, 10>, 10> &field){
    for (int row = 0; row < field.size(); ++row){
        for (int col = 0; col < field.size(); ++col){
            field.at(row).at(col) = rand() % 9;
        }
    }
}

int main(){

    srand(static_cast<unsigned int>(time(0)));
    std::array<std::array<int, 10>, 10> field_pc;
    std::array<std::array<int, 10>, 10> field_user;
    field_pc.fill({0,0});
    field_user.fill({0,0});

    fillField(field_pc);
    fillField(field_user);

    printTwoFields(field_pc, field_user);

    return 0;
}
