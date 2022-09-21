//////////////////////////////////////////////////////////////////////////////////////////////
/*
    Battleship game. AU. 09-2022.

    this is a personal challenge project.
    an attempt to recreated the Battleship classic game without looking at other examples.
    the code might be a bit too spaggetti, oh well lol.

*/
/////////////////////////////////////////////////////////////////////////////////////////////

/*

    TODO:
        1. CHeck for errors
    FEATURES:
        1. Make TCP/IP client-server

*/

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <ctime>
#include <thread>
#include <chrono>
#include <map>
#include <algorithm>

#ifdef _WIN32
#define CLS "cls"
#include <windows.h>
#endif
#ifdef __APPLE__
#define CLS "clear"
#endif

typedef std::map<std::string, std::vector<std::pair<int, int>>> Map;

enum class Player{
    User,
    Pc
};

// enum class Ship{

//     Submarine = 1,
//     Cruiser = 2,
//     Battleship = 3,
//     Carrier = 4

// };

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
void printFields(std::array<std::array<int, 10>, 10> const &field_pc, std::array<std::array<int, 10>, 10> const &field_user, int visible){

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
    const char c_BORDER = '.';
    const char c_BORDERHIT = '~';

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
                SetConsoleTextAttribute(hConsole, 9); 
                #endif
                std::cout << c_BORDERHIT << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 7);
                #endif
            }
            //missed hit
            else if (field_user.at(row).at(col) == static_cast<int>(FieldCellStates::Miss)){
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 9); //4 dark red, light blue 11
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
                if (visible == 1)
                    std::cout << c_SHIP << " ";
                else
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
                std::cout << c_BORDER << " ";
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
                SetConsoleTextAttribute(hConsole, 4); //4 dark red
                #endif
                std::cout << c_BORDERHIT << " ";
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

void checkHitField(std::array<std::array<int, 10>, 10> &field){

    const int y[] = { -1, -1, -1, 1, 1, 1, 0, 0 };// 8 directions
    const int x[] = { -1, 0, 1, -1, 0, 1, -1, 1 };// for checking

    //check in boundary

    for(int row = 0; row < field.size(); ++row){
        for(int col = 0; col < field.size(); ++col){

            if (field.at(row).at(col) == 2){

                for(int i=0; i < 8; ++i) { // looking around cell
                    if (inField(row+y[i], col+x[i])){
                        if(field.at(row+y[i]).at(col+x[i]) != 2)
                        field.at(row+y[i]).at(col+x[i]) = 7;
                    }
                }
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

void generateFirstShip(std::array<std::array<int, 10>, 10> &field, std::map<std::string, std::vector<std::pair<int, int>>> &map){

    checkField(field);
    int row{0}, col{0}, dir{0};
    const std::string ship = "ship4";
    std::vector<std::pair<int, int>> temp_vec;

    do{ //iterate while coords are not good enough
        row = getRandomNumber(0, 9);
        col = getRandomNumber(0, 9);
        dir = getRandomNumber(0, 1);

    } while (!(field.at(row).at(col) != 1 && field.at(row).at(col) != 8 && (row+4) < 9 && (col+4) < 9));

    if ((col + 4) >= 9) col = 4;
    
    for (int i = 0; i < 4; ++i){
        if (dir == 0){ //horizontal location
            field.at(row).at(col+i) = 1;
            temp_vec.emplace_back(row, col+i);
        }
        else{ //vertical
            field.at(row+i).at(col) = 1;
            temp_vec.emplace_back(row+i, col);
        }
        }

        map.emplace(ship, temp_vec);
}

void setShips(std::array<std::array<int, 10>, 10> &field, std::map<std::string, std::vector<std::pair<int, int>>> &map, std::vector<std::pair<int, int>> &vec, int &dir, int ship, std::string ship_name){
    
    checkField(field);
    getPossibles(field, vec, dir, ship);
    std::vector<std::pair<int, int>> temp_vec;

    int i = rand() % vec.size(); //choose random ship position that can be definitely installed
    int row = vec[i].first;
    int col = vec[i].second;

    for (int i = 0; i < ship; ++i){
        if (dir == 0){
            field.at(row).at(col+i) = 1;
            temp_vec.emplace_back(row, col+i);
        }
        else{
            field.at(row+i).at(col) = 1;
            temp_vec.emplace_back(row+i, col);
        }
    }

    map.emplace(ship_name, temp_vec);
}

void encodeCoords(std::string &coord, int row, int col){

    switch(row){
            case 0:
                coord = "A";
                break;
            case 1:
                coord = "B";
                break;
            case 2:
                coord = "C";
                break;
            case 3:
                coord = "D";
                break;
            case 4:
                coord = "E";
                break;
            case 5:
                coord = "F";
                break;
            case 6:
                coord = "G";
                break;
            case 7:
                coord = "H";
                break;
            case 8:
                coord = "I";
                break;
            case 9:
                coord = "J";
                break;
        }

    switch(col){
                case 0:
                    coord += "0";
                    break;
                case 1:
                    coord += "1";
                    break;
                case 2:
                    coord += "2";
                    break;
                case 3:
                    coord += "3";
                    break;
                case 4:
                    coord += "4";
                    break;
                case 5:
                    coord += "5";
                    break;
                case 6:
                    coord += "6";
                    break;
                case 7:
                    coord += "7";
                    break;
                case 8:
                    coord += "8";
                    break;
                case 9:
                    coord += "9";
                    break;
            }

}

void decodeCoords(std::string coord, int *row, int *col){

    switch(coord[0]){
            case 'A':
                *(row) = 0;
                break;
            case 'B':
                *(row) = 1;
                break;
            case 'C':
                *(row) = 2;
                break;
            case 'D':
                *(row) = 3;
                break;
            case 'E':
                *(row) = 4;
                break;
            case 'F':
                *(row) = 5;
                break;
            case 'G':
                *(row) = 6;
                break;
            case 'H':
                *(row) = 7;
                break;
            case 'I':
                *(row) = 8;
                break;
            case 'J':
                *(row) = 9;
                break;
        }

        switch(coord[1]){
            case '0':
                *(col) = 0;
                break;
            case '1':
                *(col) = 1;
                break;
            case '2':
                *(col) = 2;
                break;
            case '3':
                *(col) = 3;
                break;
            case '4':
                *(col) = 4;
                break;
            case '5':
                *(col) = 5;
                break;
            case '6':
                *(col) = 6;
                break;
            case '7':
                *(col) = 7;
                break;
            case '8':
                *(col) = 8;
                break;
            case '9':
                *(col) = 9;
                break;
        }
}

//remove PC moves around destroyed ship
void removeMissedMoves(std::array<std::array<int, 10>, 10> const &field_user, std::vector<std::string> &pc_moves){ 
        
        std::string temp_coord;
        std::vector<std::string>::iterator it;

        for(int row = 0; row < field_user.size(); ++row){
            for(int col = 0; col < field_user.size(); ++col){
                if (field_user.at(row).at(col) == static_cast<int>(FieldCellStates::BorderHit)){
                    encodeCoords(temp_coord, row, col);
                    it = std::find(pc_moves.begin(), pc_moves.end(), temp_coord);
                    if(it != pc_moves.end()){
                        int del = it - pc_moves.begin();
                        pc_moves.erase(pc_moves.begin() + del);
                    }
                }
            }
        }
}

//checking which ship is got hit
bool checkMap(std::map<std::string, std::vector<std::pair<int, int>>> &map, int row, int col, std::array<std::array<int, 10>, 10> &field,
              std::string &message, std::string &keyShipHit, std::vector<std::string> &pc_moves, Player player){

    for(auto& [key, value] : map){

            for (int i = 0; i < value.size(); ++i){
                if(value[i].first == row && value[i].second == col){
                    if (value.size() != 1){
                        if (player == Player::User)
                            message = "  You hit a ship!";
                        else{
                            message = "  PC hit your ship!";
                            keyShipHit = key;
                        }
                    }
                    value.erase(value.begin()+i);
                }

                if (value.empty()){
                    if (player == Player::User){
                        message = "  Wow! You sank a ship!";
                        checkHitField(field);
                    }
                    else{
                        message = "  Oops, PC sank your ship!";
                        checkHitField(field);
                        removeMissedMoves(field, pc_moves);
                    }

                    map.erase(key);
                }
            }
    }

    if(map.empty()){
        return true;
    }

    return false;
}

void printMap(std::map<std::string, std::vector<std::pair<int, int>>> const &map){

    std::cout << "map size " << map.size() << "\n";

    for(auto& [key, value] : map){
            std::cout << key << ": ";
            for (int i = 0; i<value.size(); ++i){
                std::cout << value[i].first << "." << value[i].second << " ";
                }
                std::cout << std::endl;
        }
}

void createGameField(std::array<std::array<int, 10>, 10> &field,
                     std::vector<std::pair<int, int>> &vec, int &dir,
                     std::map<std::string, std::vector<std::pair<int, int>>> &map){

    createField(field);
    generateFirstShip(field, map);
    setShips(field, map, vec, dir, 3, "ship3_1");
    setShips(field, map, vec, dir, 3, "ship3_2");
    setShips(field, map, vec, dir, 2, "ship2_1");
    setShips(field, map, vec, dir, 2, "ship2_2");
    setShips(field, map, vec, dir, 2, "ship2_3");
    setShips(field, map, vec, dir, 1, "ship1_1");
    setShips(field, map, vec, dir, 1, "ship1_2");
    setShips(field, map, vec, dir, 1, "ship1_3");
    setShips(field, map, vec, dir, 1, "ship1_4");
    checkField(field);
}

bool isInputValid(std::array<std::array<int, 10>, 10> &field_pc, std::string &coord){ //check if user makes correct input

    if ((coord[0] == 'A' || coord[0] == 'B' ||
         coord[0] == 'C' || coord[0] == 'D' ||
         coord[0] == 'E' || coord[0] == 'F' ||
         coord[0] == 'G' || coord[0] == 'H' ||
         coord[0] == 'I' || coord[0] == 'J')
         &&
        (coord[1] == '0' || coord[1] == '1' ||
         coord[1] == '2' || coord[1] == '3' ||
         coord[1] == '4' || coord[1] == '5' ||
         coord[1] == '6' || coord[1] == '7' ||
         coord[1] == '8' || coord[1] == '9') && coord.size() == 2){

            checkField(field_pc);
            int row{0}, col{0};
            decodeCoords(coord, &row, &col);

        if (field_pc.at(row).at(col) == static_cast<int>(FieldCellStates::Miss) ||
            field_pc.at(row).at(col) == static_cast<int>(FieldCellStates::BorderHit) ||
            field_pc.at(row).at(col) == static_cast<int>(FieldCellStates::Hit)){
                std::cout << "You've already hit there! Try again.\n";
                return false;
            }

            return true; 
         }
    else{
        std::cout << "Wrong coordinates! Try again.\n";
        return false;
    }
    return false;
}

bool userMove(std::array<std::array<int, 10>, 10> &field_pc, int row, int col){

    if (field_pc.at(row).at(col) == static_cast<int>(FieldCellStates::Ship)){
            field_pc.at(row).at(col) = static_cast<int>(FieldCellStates::Hit);
            return true;
        }

        else{
            if(field_pc.at(row).at(col) != static_cast<int>(FieldCellStates::Hit) &&
               field_pc.at(row).at(col) != static_cast<int>(FieldCellStates::Miss)) {
                field_pc.at(row).at(col) = static_cast<int>(FieldCellStates::Miss);
                return false;
            }
            return false;
        }
    return false;
}

void getPcCoord(std::array<std::array<int, 10>, 10> &field_user, std::vector<std::string> &pc_moves,
                std::map<std::string, std::vector<std::pair<int, int>>> map_user, std::string &pcLastMove,
                int &pc_row, int &pc_col, std::string const &keyShipHit){

    int move{0};
    std::string temp_pcMove = "";
    std::vector<std::string>::iterator it;

    if (pc_moves.size() > 0){

        std::cout << "   PC is attacking";
        for (int c = 0; c < 3; ++c){
            std::cout << ".";
            std::this_thread::sleep_for(std::chrono::milliseconds(250)); //400 ms
        }

        if (map_user[keyShipHit].size() == 0){

            move = rand() % pc_moves.size();
            pcLastMove = pc_moves.at(move);
            decodeCoords(pcLastMove, &pc_row, &pc_col);

        }else{

            pc_row = map_user[keyShipHit][0].first;
            pc_col = map_user[keyShipHit][0].second;

            encodeCoords(temp_pcMove, pc_row, pc_col);

            it = std::find(pc_moves.begin(), pc_moves.end(), temp_pcMove);

            if(it != pc_moves.end()){
                move = it - pc_moves.begin();
                pcLastMove = pc_moves.at(move);
            }
            
        }

        std::cout << " " << pc_moves.at(move) << std::endl;
        pc_moves.erase(pc_moves.begin() + move);

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(600)); //700 ms
}

bool pcMove(std::array<std::array<int, 10>, 10> &field_user, int row, int col){

        if (field_user.at(row).at(col) == static_cast<int>(FieldCellStates::Ship)){
                field_user.at(row).at(col) = static_cast<int>(FieldCellStates::Hit);
                return true;
        }else{
                if(field_user.at(row).at(col) != static_cast<int>(FieldCellStates::Hit) &&
                field_user.at(row).at(col) != static_cast<int>(FieldCellStates::Miss)) {
                    field_user.at(row).at(col) = static_cast<int>(FieldCellStates::Miss);
                }
            }     
    return false;
}

void createPcMoveTable(std::vector<std::string> &pc_moves){
    const std::string letters = "ABCDEFGHIJ";

    for (int i = 0; i <= 9; ++i){
        for(int j = 0; j <= 9; ++j){
            pc_moves.push_back(letters[i]+std::to_string(j));
        }
    }
}

void printUpdateMessage(Map map_user, Map map_pc, std::string message_user, std::string message_pc, std::string userLastMove, std::string pcLastMove){
        std::cout << "       Your ships: " << map_user.size();
        std::cout << "\t\t" << message_user << std::endl;

        std::cout << "         PC ships: " << map_pc.size();
        std::cout << "\t\t" << message_pc << std::endl;

        std::cout << "   Your last move: " << userLastMove << std::endl;
        std::cout << "     PC last move: " << pcLastMove << std::endl;
        
        std::cout << std::endl;
}

void printCongrats(Player player){

    std::string message_congrats = "";

    if (player == Player::User)
        message_congrats = "\t    *** CONGRATULATIONS! YOU WON!!! ***\n";
    else
        message_congrats = "\t             *** YOU LOST!!! ***\n";

    for (auto const& l : message_congrats){
        std::cout << l;
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); //400 ms
    }

    std::cout << std::endl;
}

void startMessage(){

    system(CLS);
    std::string ver = "1.1";

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::string message_start = "\t\tB A T T L E S H I P  by  AU  " + ver;

    for (auto const& l : message_start){
        std::cout << l;
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); //400 ms
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
}

void printMoveTable(std::vector<std::string> const &pc_moves){
    int a{0};
        for (int i = 0; i < pc_moves.size(); ++i){
            std::cout << pc_moves[i] << " ";
            ++a;
            if (a % 10 == 0) std::cout << std::endl;
        }
         std::cout << std::endl;
}

int playAgain(){

	char exit;

	do{
		std::cout << "  Would you like to play again (y/n)?: ";
		std::cin >> exit;

        if (exit == 'y'){
			return 1;
			break;
		}else if(exit == 'n'){
			std::cout << "  Thank you for playing. See you!" << std::endl;
			return 0;
			break;
		}else{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
    		std::cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера
		}

	}while(1);

	std::cout << std::endl;
}

int main(){

    startMessage();
    
    srand(static_cast<unsigned int>(time(0)));
    
    std::array<std::array<int, 10>, 10> field_user; //store user main field
    std::array<std::array<int, 10>, 10> field_pc;   //store pc main field

    std::map<std::string, std::vector<std::pair<int, int>>> map_user; //store user ships coords
    std::map<std::string, std::vector<std::pair<int, int>>> map_pc;   //stire pc ships coords

    std::vector<std::pair<int, int>> vec; //store coords of where ships can be installed
    std::vector<std::string> pc_moves; //store pc moves

    //game loop
    do{
        system(CLS);
        int dir{0};
        createGameField(field_pc, vec, dir, map_pc);
        createGameField(field_user, vec, dir, map_user);

        createPcMoveTable(pc_moves);
        printFields(field_pc, field_user, 0);
        
        int row{0}, col{0};
        int pc_row{0}, pc_col{0};

        std::string coord = "";
        std::string userLastMove = "";
        std::string keyShipHit = "";
            
        while(1){

            do{
                std::cout << "Enter row and column (eg. A0 or a0, or 'n' to exit):> ";
                std::cin >> coord;
                coord[0] = std::toupper(coord[0]);
                if (coord == "N"){
                    std::cout << "See you, bye!\n\n";
                    return 0;
                }
                
            } while(!isInputValid(field_pc, coord));

            system(CLS);

            userLastMove = coord;
            std::string pcLastMove;

            decodeCoords(coord, &row, &col);

            checkField(field_pc);
            checkField(field_user);

            std::string message_user = "";
            std::string message_pc = "";

            //user move
            if(userMove(field_pc, row, col)){
                if(checkMap(map_pc, row, col, field_pc, message_user, keyShipHit, pc_moves, Player::User)){
                        system(CLS);
                        printFields(field_pc, field_user, 1);
                        printCongrats(Player::User);
                        break;
                }
            }else{
                message_user = "  You missed.";
            }

            printFields(field_pc, field_user, 0);
            printUpdateMessage(map_user, map_pc, message_user, message_pc, userLastMove, pcLastMove);

            //pc move
            getPcCoord(field_user, pc_moves, map_user, pcLastMove, pc_row, pc_col, keyShipHit);
            if (pcMove(field_user, pc_row, pc_col)){
                if(checkMap(map_user, pc_row, pc_col, field_user, message_pc, keyShipHit, pc_moves, Player::Pc)){
                        system(CLS);
                        printFields(field_pc, field_user, 1);
                        printCongrats(Player::Pc);
                        break;
                }
            }else{
                message_pc = "  PC missed.";
            }

            system(CLS);
            printFields(field_pc, field_user, 0);
            printUpdateMessage(map_user, map_pc, message_user, message_pc, userLastMove, pcLastMove);

            }
    }while(playAgain());

    std::cout << std::endl;
    return 0;
}
