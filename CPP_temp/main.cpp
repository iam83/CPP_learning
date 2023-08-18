#include <iostream>
#include <array>

// Define a class with a two-dimensional array
class Field {
public:
    std::array<std::array<int, 10>, 10> field;

    Field(int x) {
        field.fill({x})
    }

    void changeCell(int row, int col, int value){
            field[row][col] = value;

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

};


int main() {

    // Create two objects of MyClass
    Field field_pc(0);
    Field field_user(0);

    Game game;
    game.printObjectsField(field_pc, field_user);

    field_pc.changeCell(7, 3, 8);
    field_user.changeCell(2, 6, 5);
    
    game.printObjectsField(field_pc, field_user);
    //printObjectsField(field_pc, field_user);

    return 0;
}