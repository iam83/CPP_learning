#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <ctime>
#include <thread>
#include <chrono>

#ifdef _WIN32
#define CLS "cls"
#include <windows.h>
#endif
#ifdef __APPLE__
#define CLS "clear"
#endif

/*

    TODO:
        1. Add PC moves and hits
        2. Update checkHitField()
    FEATURES:
        1. Make TCP/IP client-server

*/

// A simplified version of Battleship game. An attemp to make it from scratch without looking at other examples.
//
// create 10x10 field_pc
// fill cells with random located ships.
//
// 4* ships - 1
// 3* ships - 2
// 2* ships - 3
// 1* ships - 4
//
// create game loop
//      print your field_pc
//      print enemy's field_pc
//      ask user to enter coords to shot
//      check if user hits succsefully
//          if yes then update enemy's field_pc
//          else let enemy to hit
//      choose random coord to shoot
//      check if enemy hits succsefully
//      if yes then update user's field_pc
//      else ask user to eneter coords to shot

typedef std::vector<std::pair<int, int>> Coord;

enum class Player{
    User,
    Pc
};

enum class FieldCellStates{
    Ship = 1,
    Hit = 2,
    Miss = 3,
    BorderHit = 7,
    Border = 8
};

int getRandomNumber(int min, int max){
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        return static_cast<int>(rand() * fraction * (max - min + 1) + min);
     }

void createField(std::array<std::array<int, 10>, 10> &field){
    field.fill({0,0});
}

//print both fields, make it colorful on windows
void printTwoFields(std::array<std::array<int, 10>, 10> const &field_pc, std::array<std::array<int, 10>, 10> const &field_user){

    #ifdef _WIN32
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif
    std::cout << std::endl;
    std::string letters = "ABCDEFGHIJ";
    std::string separator = "        ";
    std::cout << "      ";

    const char c_SHIP = '#';
    const char c_HIT = 'X';
    const char c_MISS = '~';
    const char c_FIELD = '.';
    const char c_BORDER = '-';

    for (int c = 0; c < 10; ++c){
        std::cout << c << " ";
    }

    std::cout << separator + "   ";

    for (int c = 0; c < 10; ++c){
        std::cout << c << " ";
    }

    std::cout << std::endl;

    for (int row = 0; row < field_user.size(); ++row){
        std::cout << "   " << letters[row] << "  "; //row number
        
        // user field
        for (int col = 0; col < field_user.size(); ++col){
             if (field_user.at(row).at(col) == static_cast<int>(FieldCellStates::Ship)){
                #ifdef _WIN32
                    SetConsoleTextAttribute(hConsole, 14); //set console color font green 10, yellow 14, or 22 for selected
               
                #endif
                std::cout << c_SHIP << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //border around ship
            else if (field_user.at(row).at(col) == static_cast<int>(FieldCellStates::Border)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 8); //set console color font green 10, yellow 14
                #endif
                std::cout << c_FIELD << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //ship is hit
            else if (field_user.at(row).at(col) == static_cast<int>(FieldCellStates::Hit)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 12); //red
                #endif
                std::cout << c_HIT << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //border around hitted ship
            else if (field_user.at(row).at(col) == static_cast<int>(FieldCellStates::BorderHit)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 8); 
                #endif
                std::cout << c_BORDER << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //missed hit
            else if (field_user.at(row).at(col) == static_cast<int>(FieldCellStates::Miss)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 4); //light blue 11
                #endif
                std::cout << c_MISS << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //just empty field
            else{
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 8); //set console color font grey 8,
                #endif
                std::cout << c_FIELD << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
                }
            }

        std::cout << separator;
        std::cout << letters[row] << "  ";

        // pc field
        for (int col = 0; col < field_pc.size(); ++col){            
            if (field_pc.at(row).at(col) == static_cast<int>(FieldCellStates::Ship)){
                #ifdef _WIN32
                //set console color font green 10, yellow 14, 11 light blue, 13 magenta, 9 dark blue or 22 for selected
                SetConsoleTextAttribute(hConsole, 8);                    
                #endif
                std::cout << c_FIELD << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //border around ship
            else if (field_pc.at(row).at(col) == static_cast<int>(FieldCellStates::Border)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 8); //set console color font green 10, yellow 14
                #endif
                std::cout << c_FIELD << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //ship is hit
            else if (field_pc.at(row).at(col) == static_cast<int>(FieldCellStates::Hit)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 10); //red
                #endif
                std::cout << c_HIT << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //border around hitted ship
            else if (field_pc.at(row).at(col) == static_cast<int>(FieldCellStates::BorderHit)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 8); 
                #endif
                std::cout << c_BORDER << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //missed hit
            else if (field_pc.at(row).at(col) == static_cast<int>(FieldCellStates::Miss)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 4); //light blue 11
                #endif
                std::cout << c_MISS << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //just empty field
            else{
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 8); //set console color font grey 8,
                #endif
                std::cout << c_FIELD << " ";
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

void printVec(std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &vec){
    for(auto const &v : vec){
        std::cout << v.first.first << "." << v.first.second << " - " << v.second.first << "." << v.second.second << " / ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

bool inField(int r, int c)
{
  if( r < 0 || r > 9 ) return false;
  if( c < 0 || c > 9 ) return false;
    return true;
}

//checking field's cells and fill borders around ships
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

void checkHitField(std::array<std::array<int, 10>, 10> &field, int row, int col){

    const int y[] = { -1, -1, -1, 1, 1, 1, 0, 0 };// 8 directions
    const int x[] = { -1, 0, 1, -1, 0, 1, -1, 1 };// for checking

    //check in boundary
    if (field.at(row).at(col) == 2){
        for(int i=0; i < 8; ++i) { // looking around cell
            if (inField(row+y[i], col+x[i])){
                if(field.at(row+y[i]).at(col+x[i]) == 2)
                    field.at(row).at(col) = 7;
            }
        }
    }
}

//making vector of coords possible ships to be setup on field
void getPossibles(std::array<std::array<int, 10>, 10> const &field,
                  std::vector<std::pair<int, int>> &vec, int &dir, int ship){
    
    dir = getRandomNumber(0, 1);

    int count {0}, temp_row{0}, temp_col{0};
    vec.clear();

    if (dir == 0){
        //horizontal check
        for (int row = 0; row < field.size(); ++row){        
            for (int col = 0; col < field.size(); ++col){
                if (field.at(row).at(col) != 1 && field.at(row).at(col) != 8){
                        if (count == 0){
                            temp_col = col;
                            temp_row = row;
                        }
                        count++;
                        if (col == 9 && count < ship){
                            count = 0;
                            }
                        if (count == ship){
                            vec.push_back(std::make_pair(temp_row, temp_col));
                            count = 0;
                            }
                }else{
                        count = 0;
                    }
            }
        }
    }else{
        //vertical check
        for (int col = 0; col < field.size(); ++col){        
            for (int row = 0; row < field.size(); ++row){
                if (field.at(row).at(col) != 1 && field.at(row).at(col) != 8){
                        if (count == 0){
                            temp_col = col;
                            temp_row = row;
                        }
                        count++;
                        if (row == 9 && count < ship){
                            count = 0;
                            }
                        if (count == ship){
                            vec.push_back(std::make_pair(temp_row, temp_col));
                            count = 0;
                            }
                }else{
                        count = 0;
                    }
            }
        }
    }
}

void generateFirstShip(std::array<std::array<int, 10>, 10> &field){

    checkField(field);
    int row{0}, col{0}, dir{0};
    
    do{ //iterate while coords are not good enough
        row = getRandomNumber(0, 9);
        col = getRandomNumber(0, 9);
        dir = getRandomNumber(0, 1);

    } while (!(field.at(row).at(col) != 1 && field.at(row).at(col) != 8 && (row+4) < 9 && (col+4) < 9));

    if ((col + 4) >= 9) col = 4;
    
    for (int i = 0; i < 4; ++i){
        if (dir == 0) //horizontal location
            field.at(row).at(col+i) = 1;
        else //vertical
            field.at(row+i).at(col) = 1;
        }
}

void setShips(std::array<std::array<int, 10>, 10> &field,
              std::vector<std::pair<int, int>> &vec, int &dir, int ship){
    
    checkField(field);
    getPossibles(field, vec, dir, ship);

    int i = rand() % vec.size(); //choose random ship position that can be definitely installed
    int row = vec[i].first;
    int col = vec[i].second;

    for (int i = 0; i < ship; ++i){
        if (dir == 0)
            field.at(row).at(col+i) = 1;
        else
            field.at(row+i).at(col) = 1;
    }
}

void createGameField(std::array<std::array<int, 10>, 10> &field,
                     std::vector<std::pair<int, int>> &vec, int &dir){

    createField(field);
    generateFirstShip(field);
    setShips(field, vec, dir, 3);
    setShips(field, vec, dir, 3);
    setShips(field, vec, dir, 2);
    setShips(field, vec, dir, 2);
    setShips(field, vec, dir, 2);
    setShips(field, vec, dir, 1);
    setShips(field, vec, dir, 1);
    setShips(field, vec, dir, 1);
    setShips(field, vec, dir, 1);
}

bool isInputValid(std::string &coord, std::string userLastMove){ //check if user makes correct input
    
    if (coord == userLastMove){
        std::cout << "You've already hit there! Try again.\n";
        return false;
    }

    if(coord.size() > 2){
        std::cout << "Wrong coordinates! Try again.\n";
        return false;
    }
    if ((coord[0] == 'A' ||
         coord[0] == 'B' ||
         coord[0] == 'C' ||
         coord[0] == 'D' ||
         coord[0] == 'E' ||
         coord[0] == 'F' ||
         coord[0] == 'G' ||
         coord[0] == 'H' ||
         coord[0] == 'I' ||
         coord[0] == 'J')
         &&
        (coord[1] == '0' ||
         coord[1] == '1' ||
         coord[1] == '2' ||
         coord[1] == '3' ||
         coord[1] == '4' ||
         coord[1] == '5' ||
         coord[1] == '6' || 
         coord[1] == '7' ||
         coord[1] == '8' ||
         coord[1] == '9')){
            return true;
         }
    else{
        std::cout << "Wrong coordinates! Try again.\n";
        return false;
    }
    return false;
}

void decodeCoords(std::string coord, int &row, int &col){
    switch(coord[0]){
            case 'A':
                row = 0;
                break;
            case 'B':
                row = 1;
                break;
            case 'C':
                row = 2;
                break;
            case 'D':
                row = 3;
                break;
            case 'E':
                row = 4;
                break;
            case 'F':
                row = 5;
                break;
            case 'G':
                row = 6;
                break;
            case 'H':
                row = 7;
                break;
            case 'I':
                row = 8;
                break;
            case 'J':
                row = 9;
                break;
        }

        switch(coord[1]){
            case '0':
                col = 0;
                break;
            case '1':
                col = 1;
                break;
            case '2':
                col = 2;
                break;
            case '3':
                col = 3;
                break;
            case '4':
                col = 4;
                break;
            case '5':
                col = 5;
                break;
            case '6':
                col = 6;
                break;
            case '7':
                col = 7;
                break;
            case '8':
                col = 8;
                break;
            case '9':
                col = 9;
                break;
        }
}

bool pcMove(std::array<std::array<int, 10>, 10> &field_user, std::vector<std::string> &pc_moves, std::string &pcLastMove){

    if (pc_moves.size() > 0){

        std::cout << std::endl;
        std::cout << "   PC is shooting";
        for (int c = 0; c < 3; ++c){
            std::cout << ".";
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
        }
        int move = rand() % pc_moves.size();
        std::string letters = "ABCDEFGHIJ";

        std::cout << pc_moves.at(move) << std::endl;
        pcLastMove = pc_moves.at(move);
        pc_moves.erase(pc_moves.begin() + move);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        int row, col;
        decodeCoords(pcLastMove, row, col);

        if (field_user.at(row).at(col) == static_cast<int>(FieldCellStates::Ship)){
                field_user.at(row).at(col) = static_cast<int>(FieldCellStates::Hit);
                return true;
        }else{
                if(field_user.at(row).at(col) != static_cast<int>(FieldCellStates::Hit) &&
                field_user.at(row).at(col) != static_cast<int>(FieldCellStates::Miss)) {
                    field_user.at(row).at(col) = static_cast<int>(FieldCellStates::Miss);
                }
            }     
    }
    return false;
}

void createPcMoveTable(std::vector<std::string> &pc_moves){
    std::string letters = "ABCDEFGHIJ";

    for (int i = 0; i <= 9; ++i){
        for(int j = 0; j <= 9; ++j){
            pc_moves.push_back(letters[i]+std::to_string(j));
        }
    }
}

void printPcMoveTable(std::vector<std::string> &pc_moves){
    int c{0};
    for (auto const &m : pc_moves){
        std::cout << m << " ";
        ++c;
        if(c % 10 == 0) std::cout << std::endl;
    }
}

void printUpdateMessage(std::string message, std::string userLastMove){
        std::cout << message << std::endl;
        std::cout << "   Your last move: " << userLastMove << std::endl;
}

void printUpdateMessage(std::string message, std::string userLastMove, std::string pcLastMove){
        std::cout << message << std::endl;
        std::cout << "   Your last move: " << userLastMove << std::endl;
        std::cout << "     PC last move: " << pcLastMove << std::endl << std::endl;
}

struct Ship{
    int length;
    std::vector<std::pair<int, int>> coord;
};


int main(){

    system(CLS);
    srand(static_cast<unsigned int>(time(0)));


    // test

    Ship ship4, ship3_2, ship3_1, ship2_1, ship2_2, ship2_1, ship1_1, ship1_2, ship1_3, ship1_3, ship1_4;

    ship4.length = 4;
    ship4.coord = {{0,0}, {0,1}, {0,2}, {0,3}, {0,4}};


    //
    
    std::array<std::array<int, 10>, 10> field_user;
    std::array<std::array<int, 10>, 10> field_pc;
    std::vector<std::pair<int, int>> vec;
    std::vector<std::string> pc_moves;

    int dir{0};
    
    // field_pc = {{
    //           {1,0,1,0,0,0,0,0,0,0},
    //           {0,0,1,0,0,0,0,0,0,0},
    //           {0,0,0,0,0,0,0,0,0,0},
    //           {0,0,0,0,0,0,0,0,0,0},
    //           {0,0,0,0,0,0,0,0,0,0},
    //           {0,1,1,1,0,0,0,0,0,0},
    //           {0,0,0,0,0,0,1,0,0,0},
    //           {0,0,0,0,2,0,1,0,0,0},
    //           {0,0,0,0,0,0,0,0,0,0},
    //           {1,1,1,1,0,0,0,0,0,1}
    //         }};

    createGameField(field_pc, vec, dir);
    createGameField(field_user, vec, dir);
    checkField(field_pc);
    checkField(field_user);
    createPcMoveTable(pc_moves);
    printTwoFields(field_pc, field_user);
    
    int row{0}, col{0};
    std::string coord = "";
    std::string userLastMove = "";

    //game loop
    while(1){

        do{
            std::cout << "Enter row and column (eg. A0 or a0, or 'n' to exit):> ";
            std::cin >> coord;
            coord[0] = std::toupper(coord[0]);
            if (coord == "N"){
                std::cout << "See you, bye!\n\n";
                return 0;
            }
            
        } while(!isInputValid(coord, userLastMove));

        system(CLS);

        userLastMove = coord;
        std::string pcLastMove;

        decodeCoords(coord, row, col);

        checkField(field_pc);
        checkField(field_user);

        std::string message;

        if (field_pc.at(row).at(col) == static_cast<int>(FieldCellStates::Ship)){
            message = "   *** Nice shot! ***";
            field_pc.at(row).at(col) = static_cast<int>(FieldCellStates::Hit);
            //checkHitField(field_pc, row, col);
        }
        else{
            if(field_pc.at(row).at(col) != static_cast<int>(FieldCellStates::Hit) &&
               field_pc.at(row).at(col) != static_cast<int>(FieldCellStates::Miss)) {
                message = "   --- Missed! ---";
                field_pc.at(row).at(col) = static_cast<int>(FieldCellStates::Miss);
            }
        }

        printTwoFields(field_pc, field_user);

        printUpdateMessage(message, userLastMove);

        //pc move
        if (pcMove(field_user, pc_moves, pcLastMove)){
            message = "   !!! You got hit !!!";
        }else{
            message = "    PC missed! ";
        }
        
        system(CLS);
        printTwoFields(field_pc, field_user);

        printUpdateMessage(message, userLastMove, pcLastMove);

    }
    std::cout << std::endl;
    return 0;
}