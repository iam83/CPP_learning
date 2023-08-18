#include <iostream>
#include <array>
#include "enums.h"
#include "ccolor.h"

// Define a class with a two-dimensional array
class Field {
public:
    std::array<std::array<int, 10>, 10> field;

    Field() {
        field.fill({});
    }

    void changeCell(int row, int col, int value){
            field[row][col] = value;
    }

};

// Function to print two objects of MyClass simultaneously
void printObjectsField(const Field& field_pc, const Field& field_user) {

    std::cout << std::endl;
    const std::string letters = "ABCDEFGHIJ";
    const std::string separator = "        ";
    std::cout << "      ";

    for (int c = 0; c < 10; ++c) {
        std::cout << c << " ";
    }

    std::cout << separator << "   ";

    for (int c = 0; c < 10; ++c) {
        std::cout << c << " ";
    }

    std::cout << std::endl;

    for (int row = 0; row < field_pc.field.size(); ++row) {
        std::cout << "   " << letters[row] << "  "; //row number

        for (int col = 0; col < field_pc.field.size(); ++col) {
            if (field_pc.field[row][col] == 0) std::cout << "." << " ";
            else std::cout << field_pc.field[row][col] << " ";
        }
        
        std::cout << separator;
        std::cout << letters[row] << "  ";

        for (int col{}; col < field_user.field.size(); ++col){
            if (field_user.field[row][col] == 0) std::cout << "." << " ";
            else std::cout << field_user.field[row][col] << " ";
        }
        std::cout << std::endl;

    }
    std::cout << std::endl;
    std::cout << std::endl;
}

class Game {

public:
    void printObjectsField(const Field& field_pc, const Field& field_user) {

        std::cout << std::endl;
        const std::string letters = "ABCDEFGHIJ";
        const std::string separator = "        ";
        std::cout << "      ";

        for (int c = 0; c < 10; ++c) {
            std::cout << c << " ";
        }

        std::cout << separator << "   ";

        for (int c = 0; c < 10; ++c) {
            std::cout << c << " ";
        }

        std::cout << std::endl;

        for (int row = 0; row < field_pc.field.size(); ++row) {
            std::cout << "   " << letters[row] << "  "; //row number

            for (int col = 0; col < field_pc.field.size(); ++col) {
                if (field_pc.field[row][col] == 0) std::cout << "." << " ";
                else std::cout << field_pc.field[row][col] << " ";
            }
            
            std::cout << separator;
            std::cout << letters[row] << "  ";

            for (int col{}; col < field_user.field.size(); ++col){
                if (field_user.field[row][col] == 0) std::cout << "." << " ";
                else std::cout << field_user.field[row][col] << " ";
            }
            std::cout << std::endl;

        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    void printWarning(Warning warning){

    std::cout << setColor(CColor::LightRed);

    switch(warning){
        case Warning::TryAgain:
            std::cout << "  WARNING: You cannot install this ship there. Try again.\n";
            break;
        case Warning::TryAgainHorizontal:
            std::cout << "  WARNING: You cannot install this ship there. Try horizontal direction.\n";
            break;
        case Warning::TryAgainVertical:
            std::cout << "  WARNING: You cannot install a ship there. Try vertical direction.\n";
            break;
        case Warning::TryAgainWrongCoord:
            std::cout << "  WARNING: Wrong coordinates! Try again.\n";
            break;
        case Warning::TryAgainHitThere:
            std::cout << "  WARNING: You've already hit there! Try again.\n";
            break;
    }
    std::cout << setColor(CColor::Reset);
}

};


int main() {

    // Create two objects of Field
    Field field_pc;
    Field field_user;

    Game game;
    game.printObjectsField(field_pc, field_user);

    field_pc.changeCell(7, 3, 8);
    field_user.changeCell(2, 6, 5);
    
    game.printObjectsField(field_pc, field_user);
    //printObjectsField(field_pc, field_user);

    game.printWarning(Warning::TryAgain);
   
    return 0;
}