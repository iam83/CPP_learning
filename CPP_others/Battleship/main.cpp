#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#endif

// A simplified version of Battleship game. An attemp to make it from scratch without looking at other examples.
//
// create 10x10 field
// fill cells with random located ships.
//
// 4* ships - 1
// 3* ships - 2
// 2* ships - 3
// 1* ships - 4
//
// create game loop
//      print your field
//      print enemy's field
//      ask user to enter coords to shot
//      check if user hits succsefully
//          if yes then update enemy's field
//          else let enemy to hit
//      choose random coord to shoot
//      check if enemy hits succsefully
//      if yes then update user's field
//      else ask user to eneter coords to shot


void deb(int deb, int deb2){
    std::cout << "Debug: " << "< " << deb << " " << deb2 << " >" << "  ";
}

int getRandomNumber(int min, int max){
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        return static_cast<int>(rand() * fraction * (max - min + 1) + min);
     }

void createField(std::array<std::array<int, 10>, 10> &field){
    field.fill({0,0});
}

void checkFieldNeigh(std::array<std::array<int, 10>, 10> &field){

    for (int row = 0; row < 10; ++row){
        for (int col = 0; col < 10; ++col){

            if (field.at(row).at(col) == 0){
                if (row > 0 && row < 10 && col > 0 && col < 10){
                    if (field[row-1][col] == 1 || field[row+1][col] == 1 || field[row][col-1] == 1
                    || field[row][col+1] == 1 || field[row-1][col-1] == 1 || field[row+1][col+1] == 1
                    || field[row+1][col-1] == 1 || field[row-1][col+1] == 1)
                        field.at(row).at(col) = 8;
                }
                if (col == 0){
                    if (field[row-1][col+1] == 1)
                        field.at(row).at(col) = 8;
                }

                if (row == 0){
                    if (field[row+1][col-1] == 1 || field[row][col-1] == 1)
                        field.at(row).at(col) = 8;
                }
                if(row == 0 || col == 0)
                    if (field[row][col+1] == 1 || field[row+1][col] == 1 || field[row+1][col+1] == 1)
                        field.at(row).at(col) = 8;
                if(row == 10 || col == 10)
                    if (field[row][col-1] == 1 || field[row-1][col] == 1 || field[row-1][col-1] == 1)
                        field.at(row).at(col) = 8;
            }
                
        }
    }
}

void printField(std::array<std::array<int, 10>, 10> const &field){
    
    #ifdef _WIN32
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif

    std::string letters = "ABCDEFGHKL";
    std::cout << "   ";
    for (auto const &lett : letters){
        std::cout << lett << " ";
    }
    std::cout << std::endl;

     for (int row = 0; row < field.size(); ++row){
        SetConsoleTextAttribute(hConsole, 7);
        std::cout << row << "  ";
        for (int col = 0; col < field.size(); ++col){
            if (field.at(row).at(col) == 1){
                SetConsoleTextAttribute(hConsole, 14); //set console color font green 10, yellow 14, or 22 for selected
                std::cout << field.at(row).at(col) << " ";
                SetConsoleTextAttribute(hConsole, 7);
            }
            else if (field.at(row).at(col) == 8){
                SetConsoleTextAttribute(hConsole, 10); //set console color font green 10, yellow 14
                std::cout << field.at(row).at(col) << " ";
                SetConsoleTextAttribute(hConsole, 7);
            }
            else{
                SetConsoleTextAttribute(hConsole, 8); //set console color font grey 8,
                std::cout << field.at(row).at(col) << " ";
                SetConsoleTextAttribute(hConsole, 7);
            }
        }
        std::cout << std::endl;
    }
    
    SetConsoleTextAttribute(hConsole, 7); //set console color font white 7,
    std::cout << std::endl;
}

void generateShipsTemp(std::array<std::array<int, 10>, 10> &field, int ship){

    checkFieldNeigh(field);

    int startPoint{0}, offset{0}, dir{0};

    startPoint = getRandomNumber(0, 9);
    startPoint = getRandomNumber(0, 9);
    offset = getRandomNumber(0, 9);
    dir = getRandomNumber(0, 1);

    //deb(startPoint, rowOffset);


    if (offset + ship >= 10) offset = 6;{
        for (int i = 0; i < ship; ++i){
            if (dir == 0)
                field.at(startPoint).at(i+offset) = 1;
            else
                field.at(i+offset).at(startPoint) = 1;
            }
        }

    checkFieldNeigh(field);
}


int main(){

    std::cout << std::endl << std::endl;
    srand(static_cast<unsigned int>(time(0)));
    std::array<std::array<int, 10>, 10> field;

    createField(field);
    
    // field = {{
    //           {0,0,1,0,0,0,0,0,0,0},
    //           {0,0,1,0,0,0,0,0,0,0},
    //           {0,0,0,0,0,0,0,0,0,0},
    //           {0,0,0,0,0,0,0,0,0,0},
    //           {0,0,0,0,0,0,0,0,0,0},
    //           {0,0,0,0,0,0,0,0,0,0},
    //           {0,0,0,0,0,0,1,0,0,0},
    //           {0,0,0,0,0,0,1,0,0,0},
    //           {0,0,0,0,0,0,1,0,0,0},
    //           {0,0,0,0,0,0,1,0,0,0}
    //         }};

    printField(field);
    generateShipsTemp(field, 4);
    generateShipsTemp(field, 3);
    printField(field);

    if (field.at(2).at(5) == 1)
        std::cout << "Gotcha\n";

    return 0;
}