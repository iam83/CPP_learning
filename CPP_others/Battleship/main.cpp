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

void checkFieldNeigh2(std::array<std::array<int, 10>, 10> &field){

    for (int row = 0; row < 9; ++row){
        for (int col = 0; col < 9; ++col){

            if (field.at(row).at(col) == 0){
                if (row >=1 && row <= 8 && col >= 1 && col <= 8){
                    if (field.at(row-1).at(col) == 1 || field.at(row+1).at(col) == 1 || field.at(row).at(col-1) == 1
                    || field.at(row).at(col+1) == 1 || field.at(row-1).at(col-1) == 1 || field.at(row+1).at(col+1) == 1
                    || field.at(row+1).at(col-1) == 1 || field.at(row-1).at(col+1) == 1)
                        field.at(row).at(col) = 8;
                }
                if (col == 0){
                    if (field.at(row-1).at(col+1) == 1)
                        field.at(row).at(col) = 8;
                }

                if (row == 0){
                    if (field.at(row+1).at(col-1) == 1 || field.at(row).at(col-1) == 1)
                        field.at(row).at(col) = 8;
                }
                if(row == 0 || col == 0)
                    if (field.at(row).at(col+1) == 1 || field.at(row+1).at(col) == 1 || field.at(row+1).at(col+1) == 1)
                        field.at(row).at(col) = 8;
                if(row == 9 || col == 9)
                    if (field.at(row).at(col-1) == 1 || field.at(row-1).at(col) == 1 || field.at(row-1).at(col-1) == 1)
                        field.at(row).at(col) = 8;
            }
                
        }
    }
}

void checkFieldNeigh(std::array<std::array<int, 10>, 10> &field){

    for (int row = 0; row < field.size(); ++row){
        for (int col = 0; col < field.size(); ++col){

            if (field.at(row).at(col) == 0){
                if (row > 0 && row <= 8 && col > 0 && col <= 8){
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
                if(row == 9 || col == 9)
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
    offset = getRandomNumber(0, 9);
    dir = getRandomNumber(0, 1);

    //deb(startPoint, rowOffset);

    if (offset + ship >= 9) offset = 5;
    
    for (int i = 0; i < ship; ++i){
        if (dir == 0) //horizontal location
            field.at(startPoint).at(i+offset) = 1;
        else //vertical
            field.at(startPoint+i).at(offset) = 1;
        }


    checkFieldNeigh(field);
}

bool inField( int r, int c)
{
  if( r < 0 || r >= 10 ) return false;
  if( c < 0 || c >= 10 ) return false;
    return true;
}

int main(){

    std::cout << std::endl << std::endl;
    srand(static_cast<unsigned int>(time(0)));
    std::array<std::array<int, 10>, 10> field;

    createField(field);
    
    field = {{
              {0,0,1,0,0,0,0,0,0,0},
              {0,0,1,0,0,0,0,0,0,0},
              {0,0,0,0,0,0,0,0,0,0},
              {0,0,0,0,0,0,0,0,0,0},
              {0,0,0,0,0,0,0,0,0,0},
              {0,1,1,1,0,0,0,0,0,0},
              {0,0,0,0,0,0,1,0,0,0},
              {0,0,0,0,0,0,1,0,0,0},
              {0,0,0,0,0,0,1,0,0,0},
              {0,0,0,0,0,0,1,0,0,0}
            }};

    //generateShipsTemp(field, 4);
    //generateShipsTemp(field, 3);

    printField(field);

    const int y[] = { -1, -1, -1,  1, 1, 1,  0, 0 };// 8 shifts to neighbors
    const int x[] = { -1,  0,  1, -1, 0, 1, -1, 1 };// used in functions 

    for(int row = 1; row < field.size()-1; ++row){
        for(int col = 1; col < field.size()-1; ++col){
            for(int i=0; i<8; ++i) { // visit the 8 spaces around it
                if (field.at(row).at(col) == 0){
                    if(field.at(row+y[i]).at(col+x[i]) == 1)
                        field.at(row).at(col) = 8;
                }
            }
        }
    }

    std::cout << std::endl;

    printField(field);

    return 0;
}