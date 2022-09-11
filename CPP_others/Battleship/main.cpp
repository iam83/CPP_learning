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


int getRandomNumber(int min, int max){
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        return static_cast<int>(rand() * fraction * (max - min + 1) + min);
     }

void createField(std::array<std::array<int, 10>, 10> &field){
    field.fill({0,0});
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
        #ifdef _WIN32
            SetConsoleTextAttribute(hConsole, 7);
        #endif
        std::cout << row << "  ";
        for (int col = 0; col < field.size(); ++col){
            if (field.at(row).at(col) == 1){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 14); //set console color font green 10, yellow 14, or 22 for selected
                #endif
                std::cout << field.at(row).at(col) << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            else if (field.at(row).at(col) == 8){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 10); //set console color font green 10, yellow 14
                #endif
                std::cout << field.at(row).at(col) << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            else{
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 8); //set console color font grey 8,
                #endif
                std::cout << field.at(row).at(col) << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
        }
        std::cout << std::endl;
    }
    #ifdef _WIN32
    SetConsoleTextAttribute(hConsole, 7); //set console color font white 7,
    #endif
    std::cout << std::endl;
}

bool inField( int r, int c)
{
  if( r < 0 || r >= 9 ) return false;
  if( c < 0 || c >= 9 ) return false;
    return true;
}

void checkField(std::array<std::array<int, 10>, 10> &field){

    const int y[] = { -1, -1, -1, 1, 1, 1, 0, 0 };// 8 directions
    const int x[] = { -1, 0, 1, -1, 0, 1, -1, 1 };// for checking

    //check in boundary

    for(int row = 0; row < field.size(); ++row){
        for(int col = 0; col < field.size(); ++col){

            if (field.at(row).at(col) == 0){
                for(int i=0; i < 8; ++i) { // looking around cell
                    if (inField(row+y[i], col+x[i])){
                        if(field.at(row+y[i]).at(col+x[i]) == 1)
                            field.at(row).at(col) = 8;
                    }
                }
            }
        }
    }
}

bool checkCells(std::array<std::array<int, 10>, 10> &field, int row, int col, int ship, int dir){

    const int y[] = { -1, -1, -1, 1, 1, 1, 0, 0 };// 8 directions
    const int x[] = { -1, 0, 1, -1, 0, 1, -1, 1 };// for checking

    for (int s = 0; s < ship; ++s){
        if (dir == 0){
            for(int i=0; i < 8; ++i) {
                if (inField(row+y[i], col+x[i]+s)){
                    if(field.at(row+y[i]).at(col+x[i]+s) == 1 || field.at(row+y[i]).at(col+x[i]+s) == 8)
                        std::cout << "checkCells: FALSE\n";
                        return false;
                    }
                    else{
                        std::cout << "checkCells: TRUE\n";
                        return true;
                    }
            }
        }else{
            for(int i=0; i < 8; ++i) {
                if (inField(row+y[i]+s, col+x[i])){
                    if(field.at(row+y[i]+s).at(col+x[i]) == 1 || field.at(row+y[i]+s).at(col+x[i]) == 8)
                        std::cout << "checkCells: FALSE\n";
                        return false;
                    }
                    else{
                        std::cout << "checkCells: TRUE\n";
                        return true;
                    }
            }
        }
    }
}

bool checkCells2(std::array<std::array<int, 10>, 10> &field, int row, int col, int ship, int dir){

    const int y[] = { -1, -1, -1, 1, 1, 1, 0, 0 };// 8 directions
    const int x[] = { -1, 0, 1, -1, 0, 1, -1, 1 };// for checking
    for(int i=0; i < 8; ++i) {
     if (inField(row+y[i], col+x[i])){
        if(field.at(row+y[i]).at(col+x[i]) == 1 || field.at(row+y[i]).at(col+x[i]) == 8)
            std::cout << "checkCells: FALSE\n";
                return false;
            }else{
                std::cout << "checkCells: TRUE\n";
                return true;
                }
    }
}


bool checkPlace(std::array<std::array<int, 10>, 10> &field, int startPoint, int offset, int ship, int dir){

    int count{0};
    std::string temp_dir;

    if (dir == 0)
        temp_dir = "horizontal";
    else
        temp_dir = "vertical";


    std::cout << "ship = " << ship << std::endl;
    std::cout << "startPoint = " << startPoint << std::endl;
    std::cout << "offset = " << offset << std::endl;
    std::cout << "direction = " << temp_dir << std::endl;


    if (field.at(startPoint).at(offset) != 1 && field.at(startPoint).at(offset) != 8 && (startPoint+ship) < 9 && (offset+ship) < 9){
            std::cout << "TRUE \n\n";
            return true;
    }else{
        std::cout << "FALSE \n\n";
        return false;
    }
/*
    for (int row = 0; row < field.size(); ++row){
        for (int col = 0; col < field.size(); ++col){

            //check if startPoint not equal to existing
            if(field.at(row).at(col) != startPoint){

                for(int s = 0; s < ship; ++s){

                    if (row + ship <= 9 && col + ship <= 9){
                        if (field.at(row).at(col+s) != 1 && field.at(row).at(col+s) != 8)
                            ++count;
                        else if(field.at(row+1).at(col) !=1 && field.at(row+s).at(col) != 8)
                            ++count;
                        else return false;
                    }else return false;
                }
            }
        }
    }
    return (count > 0) ? 1 : 0;
    */
}

void generateShips(std::array<std::array<int, 10>, 10> &field, int ship){

    checkField(field);

    int startPoint{0}, offset{0}, dir{0};

    do{
    
        startPoint = getRandomNumber(0, 9);
        offset = getRandomNumber(0, 9);
        dir = getRandomNumber(0, 1);


    } while (!checkPlace(field, startPoint, offset, ship, dir));

    if ((offset + ship) >= 9) offset = 4;
    
    for (int i = 0; i < ship; ++i){
        if (dir == 0) //horizontal location
            //if (field.at(startPoint).at(i+offset) != 1 && field.at(startPoint).at(i+offset) != 8)
            field.at(startPoint).at(i+offset) = 1;
        else //vertical
        //if (field.at(startPoint).at(i+offset) != 1 && field.at(startPoint).at(i+offset) != 8)
            field.at(startPoint+i).at(offset) = 1;
        }
    checkField(field);
}

void setShips(std::array<std::array<int, 10>, 10> &field, int ship){

    int startPoint_row = getRandomNumber(0, 9);
    int startPoint_col = getRandomNumber(0, 9);

    const int y[] = { -1, -1, -1,  1, 1, 1, 0, 0 };// 8 directions
    const int x[] = { -1, 0, 1, -1, 0, 1, -1, 1 };// for checking

    std::cout << "startPoint_row = " << startPoint_row << std::endl;
    std::cout << "startPoint_col = " << startPoint_col << std::endl;
    
    field.at(startPoint_row).at(startPoint_col) = 1;

    int count {0};

    for (int row = startPoint_row; row < field.size(); ++row){        
        for (int col = startPoint_col; col < field.size(); ++col){ 
            if (field.at(row).at(col) == 0){
                for(int i=0; i < 8; ++i) { // looking around cell
                    if (inField(row+y[i], col+x[i])){
                        if(field.at(row+y[i]).at(col+x[i]) == 0)
                            ++count;
                    }
                }
            }
        }
    }
    std::cout << "count " << count << "\n";
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
    //           {0,1,1,1,0,0,0,0,0,0},
    //           {0,0,0,0,0,0,1,0,0,0},
    //           {0,0,0,0,0,0,1,0,0,0},
    //           {0,0,0,0,0,0,1,0,0,0},
    //           {0,0,0,0,0,0,1,0,0,0}
    //         }};

    setShips(field, 4);

    printField(field);
    //checkField(field);
    std::cout << std::endl;


    return 0;
}
