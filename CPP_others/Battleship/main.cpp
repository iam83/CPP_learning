#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <ctime>

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

typedef std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> Coord;

enum class Player{
    User,
    Pc
};

enum class FieldStates{
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

    for (auto const &lett : letters){
        std::cout << lett << " ";
    }

    std::cout << separator + "   ";

    for (auto const &lett : letters){
        std::cout << lett << " ";
    }

    std::cout << std::endl;

    for (int row = 0; row < field_pc.size(); ++row){
        std::cout << "   " << row << "  "; //row number
        
        for (int col = 0; col < field_pc.size(); ++col){// user field
            //std::cout << field_user.at(row).at(col) << " ";
             if (field_user.at(row).at(col) == static_cast<int>(FieldStates::Ship)){
                #ifdef _WIN32
                    SetConsoleTextAttribute(hConsole, 14); //set console color font green 10, yellow 14, or 22 for selected
               
                #endif
                std::cout << "#" << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //border around ship
            else if (field_user.at(row).at(col) == static_cast<int>(FieldStates::Border)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 8); //set console color font green 10, yellow 14
                #endif
                std::cout << "." << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //ship is hit
            else if (field_user.at(row).at(col) == static_cast<int>(FieldStates::Hit)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 12); //red
                #endif
                std::cout << "X" << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //border around hitted ship
            else if (field_user.at(row).at(col) == static_cast<int>(FieldStates::BorderHit)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 8); 
                #endif
                std::cout << "-" << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //missed hit
            else if (field_user.at(row).at(col) == static_cast<int>(FieldStates::Miss)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 4); //light blue 11
                #endif
                std::cout << "-" << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //just empty field
            else{
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 8); //set console color font grey 8,
                #endif
                std::cout << "." << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
                }
            }

        std::cout << separator;
        std::cout << row << "  ";

        for (int col = 0; col < field_pc.size(); ++col){ // pc field
            //std::cout << field_pc.at(row).at(col) << " ";
            
            if (field_pc.at(row).at(col) == static_cast<int>(FieldStates::Ship)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 8); //set console color font green 10, yellow 14, 11 light blue, 13 magenta, 9 dark blue or 22 for selected                    
                #endif
                std::cout << "." << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //border around ship
            else if (field_pc.at(row).at(col) == static_cast<int>(FieldStates::Border)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 8); //set console color font green 10, yellow 14
                #endif
                std::cout << "." << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //ship is hit
            else if (field_pc.at(row).at(col) == static_cast<int>(FieldStates::Hit)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 12); //red
                #endif
                std::cout << "X" << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //border around hitted ship
            else if (field_pc.at(row).at(col) == static_cast<int>(FieldStates::BorderHit)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 8); 
                #endif
                std::cout << "-" << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //missed hit
            else if (field_pc.at(row).at(col) == static_cast<int>(FieldStates::Miss)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 4); //light blue 11
                #endif
                std::cout << "-" << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //just empty field
            else{
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 8); //set console color font grey 8,
                #endif
                std::cout << "." << " ";
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

//print one field
void printField(std::array<std::array<int, 10>, 10> const &field, Player player){
    
    #ifdef _WIN32
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif

    std::string letters = "ABCDEFGHIJ";
    //std::string letters = "0123456789"; //for debugging
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
            //if cells are taken by ships
            if (field.at(row).at(col) == static_cast<int>(FieldStates::Ship)){
                #ifdef _WIN32
                if(player == Player::User)
                    SetConsoleTextAttribute(hConsole, 14); //set console color font green 10, yellow 14, or 22 for selected
                else
                    SetConsoleTextAttribute(hConsole, 8); //set console color font green 10, yellow 14, 11 light blue, 13 magenta, 9 dark blue or 22 for selected                    
                #endif
                if (player == Player::User)
                    std::cout << "#" << " ";
                else
                    std::cout << "." << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //border around ship
            else if (field.at(row).at(col) == static_cast<int>(FieldStates::Border)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 8); //set console color font green 10, yellow 14
                #endif
                std::cout << "." << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //ship is hit
            else if (field.at(row).at(col) == static_cast<int>(FieldStates::Hit)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 12); //red
                #endif
                std::cout << "X" << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //border around hitted ship
            else if (field.at(row).at(col) == static_cast<int>(FieldStates::BorderHit)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 8); 
                #endif
                std::cout << "-" << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //missed hit
            else if (field.at(row).at(col) == static_cast<int>(FieldStates::Miss)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 11); //light blue
                #endif
                std::cout << "-" << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //just empty field
            else{
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 8); //set console color font grey 8,
                #endif
                std::cout << "." << " ";
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
void getPossibles(std::array<std::array<int, 10>, 10> const &field, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &vec, int &dir, int ship){
    
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
                            vec.push_back(std::make_pair(std::make_pair(temp_row, temp_col), std::make_pair(row, col)));
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
                            vec.push_back(std::make_pair(std::make_pair(temp_row, temp_col), std::make_pair(row, col)));
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

void setShips(std::array<std::array<int, 10>, 10> &field, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &vec, int &dir, int ship){
    
    checkField(field);
    getPossibles(field, vec, dir, ship);

    int i = rand() % vec.size(); //choose random ship position that can be definitely installed
    int row = vec[i].first.first;
    int col = vec[i].first.second;

    for (int i = 0; i < ship; ++i){
        if (dir == 0)
            field.at(row).at(col+i) = 1;
        else
            field.at(row+i).at(col) = 1;
    }
}

void createGameField(std::array<std::array<int, 10>, 10> &field, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> &vec, int &dir){

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

bool isInputValid(std::string &coord){ //check if user makes correct input
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

int main(){

    system(CLS);
    srand(static_cast<unsigned int>(time(0)));

    std::array<std::array<int, 10>, 10> field_user;
    std::array<std::array<int, 10>, 10> field_pc;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> vec;
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
    //printField(field_pc, Player::Pc);
    //printField(field_user, Player::User);
    printTwoFields(field_pc, field_user);
    
    int row, col;
    std::string coord;

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
            
        } while(!isInputValid(coord));

        system(CLS);

        std::string lastMove = coord;

        switch(coord[0]){
            case 'A':
                col = 0;
                break;
            case 'B':
                col = 1;
                break;
            case 'C':
                col = 2;
                break;
            case 'D':
                col = 3;
                break;
            case 'E':
                col = 4;
                break;
            case 'F':
                col = 5;
                break;
            case 'G':
                col = 6;
                break;
            case 'H':
                col = 7;
                break;
            case 'I':
                col = 8;
                break;
            case 'J':
                col = 9;
                break;
        }

        switch(coord[1]){
            case '0':
                row = 0;
                break;
            case '1':
                row = 1;
                break;
            case '2':
                row = 2;
                break;
            case '3':
                row = 3;
                break;
            case '4':
                row = 4;
                break;
            case '5':
                row = 5;
                break;
            case '6':
                row = 6;
                break;
            case '7':
                row = 7;
                break;
            case '8':
                row = 8;
                break;
            case '9':
                row = 9;
                break;
        }

        checkField(field_pc);

        std::string message;

        if (field_pc.at(row).at(col) == static_cast<int>(FieldStates::Ship)){
            message = "   *** Nice shot! ***";
            field_pc.at(row).at(col) = static_cast<int>(FieldStates::Hit);
            //checkHitField(field_pc, row, col);
        }
        else{
            if(field_pc.at(row).at(col) != static_cast<int>(FieldStates::Hit) &&
               field_pc.at(row).at(col) != static_cast<int>(FieldStates::Miss)) {
                message = "   --- Missed! ---";
                field_pc.at(row).at(col) = static_cast<int>(FieldStates::Miss);
            }
        }

        //printField(field_pc, Player::Pc);
        //printField(field_user, Player::User);

        printTwoFields(field_pc, field_user);

        std::cout << message << std::endl;
        std::cout << "   Your last move: " << lastMove << std::endl << std::endl;
    }

    std::cout << std::endl;
    return 0;
}