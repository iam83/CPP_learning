//////////////////////////////////////////////////////////////////////////////////////////////
/*
    Battleship game. AU. 09-2022.
    This is a personal challenge project.
    An attempt to recreate the Battleship classic game without looking at other examples.
    The code might look a bit too spaggetti, oh well but it works lol.

    this version meant to be a test site for optimizing the previous one
*/
/////////////////////////////////////////////////////////////////////////////////////////////
/*  
    UPDATE:
        17/08/2023 added Demo mode. PC vs PC. optimized some code
        11/08/2023 updated color output feature to make it cross-platform
*/
/*
    BUGS:
    01. PC stops moving. ??? it keeps getting moves. but in message there's always last move.

*/
/*
    TODO:
        1. Adjust PC move to make it a bit more random when hitting User's ship.
        2. Wrap into a Class
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

#include "ccolor.h"
#include "print.h"

#ifdef _WIN32
#define CLS "cls"
#endif
#ifdef __APPLE__
#define CLS "clear"
#endif


std::string g_VERSION = "1.55";

int g_TIME = 1; //TIME factor for sleep::thread. for demo mode it will x2. for debug put 0

void sleepThread(int time){
    std::this_thread::sleep_for(std::chrono::milliseconds(time * g_TIME));  
}

typedef std::map<std::string, std::vector<std::pair<int, int>>> Map;

enum Row{
    Row_A, Row_B, Row_C, Row_D, Row_E, Row_F, Row_G, Row_H, Row_I, Row_J
};

enum Col{
    Col_0, Col_1, Col_2, Col_3, Col_4, Col_5, Col_6, Col_7, Col_8, Col_9
};

struct Coord{
    Row row;
    Col col;
};


void exit_app(){
    exit(0);
}

int getRandomNumber(int min, int max) {
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void createField(std::array<std::array<int, 10>, 10>& field) {
    field.fill({ 0,0 });
}

bool inField(int row, int col)
{
    if (row < 0 || row > 9) return false;
    if (col < 0 || col > 9) return false;
    return true;
}

//checking field's cells and fill borders around ships
void checkField(std::array<std::array<int, 10>, 10>& field) {

    const int y[] = { -1, -1, -1, 1, 1, 1, 0, 0 }; // 8 directions
    const int x[] = { -1, 0, 1, -1, 0, 1, -1, 1 }; // for checking
    //check in boundary
    for (int row = 0; row < static_cast<int>(field.size()); ++row) {
        for (int col = 0; col < static_cast<int>(field.size()); ++col) {
            if (field.at(row).at(col) == FieldCellStates::Field) {
                for (int i = 0; i < 8; ++i) { // looking around cell
                    if (inField(row + y[i], col + x[i])) {
                        if (field.at(row + y[i]).at(col + x[i]) == FieldCellStates::Ship)
                            field.at(row).at(col) = FieldCellStates::Border;
                    }
                }
            }
        }
    }
}

void checkHitField(std::array<std::array<int, 10>, 10>& field) {

    const int y[] = { -1, -1, -1, 1, 1, 1, 0, 0 };// 8 directions
    const int x[] = { -1, 0, 1, -1, 0, 1, -1, 1 };// for checking

    //check in boundary

    for (int row = 0; row < static_cast<int>(field.size()); ++row) {
        for (int col = 0; col <static_cast<int>(field.size()); ++col) {

            if (field.at(row).at(col) == FieldCellStates::Hit) {

                for (int i = 0; i < 8; ++i) { // looking around cell
                    if (inField(row + y[i], col + x[i])) {
                        if (field.at(row + y[i]).at(col + x[i]) != FieldCellStates::Hit && field.at(row + y[i]).at(col + x[i]) != FieldCellStates::Ship)
                            field.at(row + y[i]).at(col + x[i]) = FieldCellStates::BorderHit;
                    }
                }
            }
        }
    }
}

//making a vector of possible coordinates where ships can be placed on the field
void getPossibles(std::array<std::array<int, 10>, 10> const &field,
    std::vector<std::pair<int, int>> &vec, int &dir, int ship) {

    dir = getRandomNumber(0, 1);

    int count{ 0 }, temp_row{ 0 }, temp_col{ 0 };
    vec.clear();

    if (dir == Direction::Horizontal) {
        //horizontal check
        for (int row = 0; row < static_cast<int>(field.size()); ++row) {
            for (int col = 0; col < static_cast<int>(field.size()); ++col) {
                if (field.at(row).at(col) != FieldCellStates::Ship && field.at(row).at(col) != FieldCellStates::Border) {
                    if (count == 0) {
                        temp_col = col;
                        temp_row = row;
                    }
                    count++;
                    if (col == 9 && count < ship) {
                        count = 0;
                    }
                    if (count == ship) {
                        vec.push_back(std::make_pair(temp_row, temp_col));
                        count = 0;
                    }
                }
                else {
                    count = 0;
                }
            }
        }
    }
    else {
        //vertical check
        for (int col = 0; col < static_cast<int>(field.size()); ++col) {
            for (int row = 0; row < static_cast<int>(field.size()); ++row) {
                if (field.at(row).at(col) != FieldCellStates::Ship && field.at(row).at(col) != FieldCellStates::Border) {
                    if (count == 0) {
                        temp_col = col;
                        temp_row = row;
                    }
                    count++;
                    if (row == 9 && count < ship) {
                        count = 0;
                    }
                    if (count == ship) {
                        vec.push_back(std::make_pair(temp_row, temp_col));
                        count = 0;
                    }
                }
                else {
                    count = 0;
                }
            }
        }
    }
}

void generateFirstShip(std::array<std::array<int, 10>, 10>& field, std::map<std::string, std::vector<std::pair<int, int>>>& map, int const ship, std::string const ship_name) {

    checkField(field);
    int row{ 0 }, col{ 0 }, dir{ 0 };
    std::vector<std::pair<int, int>> temp_vec;

    do { //iterate while coords are not good enough
        row = getRandomNumber(0, 9);
        col = getRandomNumber(0, 9);
        dir = getRandomNumber(0, 1);

    } while (!(field.at(row).at(col) != FieldCellStates::Ship && field.at(row).at(col) != FieldCellStates::Border && (row + 4) < 9 && (col + 4) < 9));

    if ((col + ship) >= 9) col = 4;

    for (int i = 0; i < ship; ++i) {
        if (dir == Direction::Horizontal) { //horizontal location
            field.at(row).at(col + i) = FieldCellStates::Ship;
            temp_vec.emplace_back(row, col + i);
        }
        else { //vertical
            field.at(row + i).at(col) = FieldCellStates::Ship;
            temp_vec.emplace_back(row + i, col);
        }
    }

    map.emplace(ship_name, temp_vec);
    checkField(field);
}

void setShips(std::array<std::array<int, 10>, 10>& field, std::map<std::string, std::vector<std::pair<int, int>>>& map,
              std::vector<std::pair<int, int>>& vec, int& dir, int ship, std::string ship_name) {

    checkField(field);
    getPossibles(field, vec, dir, ship);
    std::vector<std::pair<int, int>> temp_vec;

    int i = rand() % vec.size(); //choose random ship position where it can be definitely installed
    int row = vec[i].first;
    int col = vec[i].second;

    for (int i = 0; i < ship; ++i) {
        if (dir == Direction::Horizontal) {
            field.at(row).at(col + i) = FieldCellStates::Ship;
            temp_vec.emplace_back(row, col + i);
        }
        else {
            field.at(row + i).at(col) = FieldCellStates::Ship;
            temp_vec.emplace_back(row + i, col);
        }
    }

    map.emplace(ship_name, temp_vec);
    checkField(field);
}

void encodeCoords(std::string& coord_str, int row, int col) {

    switch (row) {
        case 0: coord_str = "A"; break;
        case 1: coord_str = "B"; break;
        case 2: coord_str = "C"; break;
        case 3: coord_str = "D"; break;
        case 4: coord_str = "E"; break;
        case 5: coord_str = "F"; break;
        case 6: coord_str = "G"; break;
        case 7: coord_str = "H"; break;
        case 8: coord_str = "I"; break;
        case 9: coord_str = "J"; break;
    }

    switch (col) {
        case 0: coord_str += "0"; break;
        case 1: coord_str += "1"; break;
        case 2: coord_str += "2"; break;
        case 3: coord_str += "3"; break;
        case 4: coord_str += "4"; break;
        case 5: coord_str += "5"; break;
        case 6: coord_str += "6"; break;
        case 7: coord_str += "7"; break;
        case 8: coord_str += "8"; break;
        case 9: coord_str += "9"; break;
    }

}

void decodeCoords(const std::string coord_str, int &row, int &col) {

    switch (coord_str[0]) {
        case 'A': row = 0; break;
        case 'B': row = 1; break;
        case 'C': row = 2; break;
        case 'D': row = 3; break;
        case 'E': row = 4; break;
        case 'F': row = 5; break;
        case 'G': row = 6; break;
        case 'H': row = 7; break;
        case 'I': row = 8; break;
        case 'J': row = 9; break;
    }
    switch (coord_str[1]) {
        case '0': col = 0; break;
        case '1': col = 1; break;
        case '2': col = 2; break;
        case '3': col = 3; break;
        case '4': col = 4; break;
        case '5': col = 5; break;
        case '6': col = 6; break;
        case '7': col = 7; break;
        case '8': col = 8; break;
        case '9': col = 9; break;
    }
}

//remove PC moves around destroyed ship
void removeMissedMoves(std::array<std::array<int, 10>, 10> const& field_user, std::vector<std::string>& pc_moves) {

    std::string temp_coord = "";
    std::vector<std::string>::iterator it;

    for (int row = 0; row < static_cast<int>(field_user.size()); ++row) {
        for (int col = 0; col < static_cast<int>(field_user.size()); ++col) {
            if (field_user.at(row).at(col) == FieldCellStates::BorderHit) {

                encodeCoords(temp_coord, row, col);

                it = std::find(pc_moves.begin(), pc_moves.end(), temp_coord);
                if (it != pc_moves.end()) {
                    int del = it - pc_moves.begin();
                    pc_moves.erase(pc_moves.begin() + del);
                }
            }
        }
    }
}

//checking which ship is got hit
bool checkMap(std::map<std::string, std::vector<std::pair<int, int>>> &map, int row, int col,
              std::array<std::array<int, 10>, 10> &field, std::string& message, std::string& keyShipHit,
              std::vector<std::string>& moves, Player player) {

    std::string temp_key = "";

    for (auto& [key, value] : map) {

        for (int i = 0; i < static_cast<int>(value.size()); ++i) {
            if (value[i].first == row && value[i].second == col) {
                if (value.size() != 1) {
                    if (player == Player::User){
                        message = "  You hit a ship!";
                        keyShipHit = key;
                    }
                    else {
                        std::string coord_str = "";
                        encodeCoords(coord_str, value[i].first, value[i].second);
                        message = "  PC hit your ship at " + coord_str;
                        keyShipHit = key;
                    }
                }
                value.erase(value.begin() + i);
            }

            if (value.empty()) {

                if (player == Player::User) {
                    message = "  Wow! You sank a ship!";
                    checkHitField(field);
                }
                else {
                    message = "  Oops, PC sank your ship!";
                    checkHitField(field);
                    removeMissedMoves(field, moves);
                }

                temp_key = key;
            }
        }
    }
    
    if (!temp_key.empty())
        map.erase(temp_key);

    if (map.empty()) {
        return true;
    }

    return false;
}

void createGameField(std::array<std::array<int, 10>, 10>& field,
    std::vector<std::pair<int, int>>& vec, int& dir,
    std::map<std::string, std::vector<std::pair<int, int>>>& map) {

    createField(field);
    generateFirstShip(field, map,  Ship::Carrier, "ship4");
    setShips(field, map, vec, dir, Ship::Battleship, "ship3_1");
    setShips(field, map, vec, dir, Ship::Battleship, "ship3_2");
    setShips(field, map, vec, dir, Ship::Cruiser, "ship2_1");
    setShips(field, map, vec, dir, Ship::Cruiser, "ship2_2");
    setShips(field, map, vec, dir, Ship::Cruiser, "ship2_3");
    setShips(field, map, vec, dir, Ship::Submarine, "ship1_1");
    setShips(field, map, vec, dir, Ship::Submarine, "ship1_2");
    setShips(field, map, vec, dir, Ship::Submarine, "ship1_3");
    setShips(field, map, vec, dir, Ship::Submarine, "ship1_4");
}

bool isInputValid(std::array<std::array<int, 10>, 10>& field_pc, std::string& coord_str) { //check if user makes correct input

    if ((coord_str[0] == 'A' || coord_str[0] == 'B' ||
         coord_str[0] == 'C' || coord_str[0] == 'D' ||
         coord_str[0] == 'E' || coord_str[0] == 'F' ||
         coord_str[0] == 'G' || coord_str[0] == 'H' ||
         coord_str[0] == 'I' || coord_str[0] == 'J')
        &&
        (coord_str[1] == '0' || coord_str[1] == '1' ||
         coord_str[1] == '2' || coord_str[1] == '3' ||
         coord_str[1] == '4' || coord_str[1] == '5' ||
         coord_str[1] == '6' || coord_str[1] == '7' ||
         coord_str[1] == '8' || coord_str[1] == '9')
        && coord_str.size() == 2) {

        checkField(field_pc);
        int row{ 0 }, col{ 0 };
        decodeCoords(coord_str, row, col);

        if (field_pc.at(row).at(col) == FieldCellStates::Miss ||
            field_pc.at(row).at(col) == FieldCellStates::BorderHit ||
            field_pc.at(row).at(col) == FieldCellStates::Hit) {
            printWarning(Warning::TryAgainHitThere);
            return false;
        }

        return true;
    }
    else {
        printWarning(Warning::TryAgainWrongCoord);
        return false;
    }
    return false;
}

bool move(std::array<std::array<int, 10>, 10>& field, int row, int col) {

    if (field.at(row).at(col) == FieldCellStates::Ship) {

        field.at(row).at(col) = FieldCellStates::Hit;
        return true;
    }

    else {
        if (field.at(row).at(col) != FieldCellStates::Hit &&
            field.at(row).at(col) != FieldCellStates::Miss) {
            field.at(row).at(col) = FieldCellStates::Miss;
            return false;
        }
        return false;
    }
    return false;
}

void getCoord(std::vector<std::string>& moves,
    std::map<std::string, std::vector<std::pair<int, int>>> map, std::string& lastMove,
    int& row, int& col, std::string const& keyShipHit, Player player) {

    int move{ 0 };
    std::string temp_pcMove = "";
    std::vector<std::string>::iterator it;

    if (moves.size() > 0) {
        if(player == Player::Pc)
            std::cout << "   PC is attacking";
        else
            std::cout << " User is attacking";
            
        for (int c = 0; c < 3; ++c) {
            std::cout << ".";
            sleepThread(150);
        }

        if (map[keyShipHit].size() == 0) {

            move = rand() % moves.size();
            lastMove = moves.at(move);
            decodeCoords(lastMove, row, col);

        }
        else {

            row = map[keyShipHit][0].first;
            col = map[keyShipHit][0].second;

            encodeCoords(temp_pcMove, row, col);

            it = std::find(moves.begin(), moves.end(), temp_pcMove);

            if (it != moves.end()) {
                move = it - moves.begin();
                lastMove = moves.at(move);
            }

        }

        std::cout << " " << moves.at(move) << std::endl;
        moves.erase(moves.begin() + move);

    }
    sleepThread(300); //600 ms
}

void createMoveTable(std::vector<std::string>& pc_moves) {

    pc_moves.clear(); //clean before creating

    const std::string letters = "ABCDEFGHIJ";
    for (int i = 0; i <= 9; ++i) {
        for (int j = 0; j <= 9; ++j) {
            pc_moves.push_back(letters[i] + std::to_string(j));
        }
    }
}

int playAgain() {

    char exit;

    do {
        std::cout << "  Would you like to play again (y/n)?: ";
        std::cin >> exit;

        if (exit == 'y' || exit == 'Y') {
            g_TIME = 1; //reset g_TIME to 1. otherwise it would accumulate the value from the previous runtime
            return 1;
            break;
        }
        else if (exit == 'n' || exit == 'N') {
            std::cout << "  Thank you for playing. See you!" << std::endl;
            return 0;
            break;
        }
        else {
            std::cin.clear(); // 
            std::cin.ignore(32767, '\n');
        }

    } while (1);

    std::cout << std::endl;
}

bool isAutomaticSetup(bool &demo){

    char exit;

    do {
        std::cout << "\n\n\n";
        std::cout << "\t\tB A T T L E S H I P  by  AU  " + g_VERSION;
        std::cout << "\n\n";
        std::cout << "        Choose ship setup mode\n\n";
        std::cout << "         'a' for Automatic\n";
        std::cout << "         'm' for Manual\n";
        std::cout << "         'd' for Demo mode\n";
        std::cout << "         'q' for Quit\n\n";
        std::cout << "          >: ";
        std::cin >> exit;
        std::cout << std::endl;
        
        if (exit == 'a' || exit == 'A') {
            std::cin.clear(); // 
            std::cin.ignore(32767, '\n');
            return true;
            break;
        }
        else if (exit == 'm' || exit == 'M') {
            std::cin.clear(); // 
            std::cin.ignore(32767, '\n');
            demo = {false};
            return false;
            break;
        }
        else if(exit == 'q' || exit == 'Q'){
            std::cout << "See you! Bye.\n\n";
            exit_app();
        }
        else if(exit == 'd' || exit == 'D'){
            //demo mode when pc vs pc
            std::cin.clear(); // 
            std::cin.ignore(32767, '\n');
            demo = {true};
            g_TIME *= 2;
            return true;
        }
        else {
            system(CLS);
            std::cin.clear(); // 
            std::cin.ignore(32767, '\n');
        }

    } while (1);

    std::cout << std::endl;
}

void setManualField(std::array<std::array<int, 10>, 10> &field_user, std::array<std::array<int, 10>, 10> &field_pc,
                    Map &map_user, std::string coord_str, char dir_char, int ship, std::vector<std::string> &ship_name){

    std::vector<std::pair<int, int>> temp_vec;
    int row{0}; int col{0};
    int dir{0};

    decodeCoords(coord_str, row, col);

    if (dir_char == 'h')
        dir = Direction::Horizontal;
    else if (dir_char == 'v')
        dir = Direction::Vertical;

    for (int i = 0; i < ship; ++i) {
        if (dir == Direction::Horizontal) {
            field_user.at(row).at(col + i) = FieldCellStates::Ship;
            temp_vec.emplace_back(row, col + i);
        }
        else {
            field_user.at(row + i).at(col) = FieldCellStates::Ship;
            temp_vec.emplace_back(row + i, col);
        }
    }

    map_user.emplace(ship_name[0], temp_vec);
    ship_name.erase(ship_name.begin());

    system(CLS);
    checkField(field_user);
    std::cout << "\tManual setup\n";
    printUserField(field_user);

}

bool isManualInputValid(char dir_char){
    if (dir_char == 'v' || dir_char == 'h') 
        return true;
    return false;
}

bool isValidToInstall(std::array<std::array<int, 10>, 10> &field_user, int row, int col){

    if(field_user.at(row).at(col) == FieldCellStates::Ship || field_user.at(row).at(col) == FieldCellStates::Border){
        printWarning(Warning::TryAgain);
        return false;
       }
    return true;
}

bool isValidToInstall(std::array<std::array<int, 10>, 10> &field_user, int row, int col, char dir_char, int ship){
    
    if ((row + ship) > 10 && (col + ship) > 10){
        printWarning(Warning::TryAgain);
        return false;
    }

    if((col + ship) < 11){
        for (int i = 0; i < ship; ++i){
                if(field_user.at(row).at(col + i) == FieldCellStates::Border){
                    continue;
                }
        }
    }
    else if((row + ship) < 11){
         for (int i = 0; i < ship; ++i){
                if(field_user.at(row + i).at(col) == FieldCellStates::Border){
                    continue;
                }
        }
    }else{
        printWarning(Warning::TryAgain);
        return false;
    }

    //checking with directions
    if (dir_char == 'v'){
        if ((row + ship) < 11){
                for (int i = 0; i < ship; ++i){
                        if(field_user.at(row + i).at(col) == FieldCellStates::Border){
                            printWarning(Warning::TryAgainHorizontal);
                            return false;
                        }
                    }
            }else{
                    printWarning(Warning::TryAgainHorizontal);
                    return false;
                 }
    }

    if (dir_char == 'h'){
        if((col + ship) < 11){
                for (int i = 0; i < ship; ++i){
                        if(field_user.at(row).at(col + i) == FieldCellStates::Border){
                            printWarning(Warning::TryAgainVertical);
                            return false;
                        }
                    }
            }else{
                printWarning(Warning::TryAgainVertical);
                return false;
                }
        }
    return true;
}

bool manualSetup(std::array<std::array<int, 10>, 10> &field_user, std::array<std::array<int, 10>, 10> &field_pc, Map &map_user, std::vector<std::string> &ship_name){

    std::string coord_str = "";
    std::string temp {};
    char dir_char = ' ';
    int ship{0};
    int row{0}; int col{0};

    checkField(field_user);
    printUserField(field_user);
    
    // create bank of ships to be installed - 4X, 3X, 3X, 2X, 2X, 2X, 1X, 1X, 1X, 1X
    std::vector<int> ship_bank = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

    bool switchToAuto = false;

    do {
        
        ship = ship_bank[0];

        do {    
                std::cout << setColor(CColor::Cyan);
                std::cout << "  Enter start Row and Column for the ";
                std::cout << setColor(CColor::Yellow);
                std::cout << ship << "X";
                std::cout << setColor(CColor::Cyan);
                std::cout << " ship\n";
                std::cout << setColor(CColor::Reset);
                std::cout << "  (eg. a0, or type 'auto', 'q' for quit): ";
                std::cin >> coord_str;


                for(auto letter : coord_str){
                    temp += std::tolower(letter); //converting string to lowercase
                } 
                coord_str = temp; temp = "";
                
                if(coord_str[0] == 'q'){
                    std::cout << "See you! Bye.\n\n";
                    exit(0);
                }

                if(coord_str == "auto"){
                    switchToAuto = true;
                    break;
                }

                coord_str[0] = std::toupper(coord_str[0]);
                
                decodeCoords(coord_str, row, col);


            } while (!isInputValid(field_user, coord_str) || !(isValidToInstall(field_user, row, col, dir_char, ship) && isValidToInstall(field_user, row, col)));

            field_user.at(row).at(col) = FieldCellStates::Ship;
            system(CLS);
            std::cout << "\tManual setup\n";
            printUserField(field_user);

        do {
                if(switchToAuto){
                    break;
                }

                if (ship == 1)
                    break;
                std::cout << "  Type 'v' for vertical or 'h' for horizontal placement: ";
                std::cin >> dir_char;
                
            } while (!isManualInputValid(dir_char) || !isValidToInstall(field_user, row, col, dir_char, ship));

        
        setManualField(field_user, field_pc, map_user, coord_str, dir_char, ship, ship_name);
        ship_bank.erase(ship_bank.begin());
        
        dir_char = ' ';

        if (switchToAuto){
            break;
        }

    } while(ship_bank.size() != 0);

    if(switchToAuto){
        return false;
    }

    return true;
}

void clearMaps(Map &map_user, Map &map_pc){
    map_user.clear();
    map_pc.clear();
}

//DEBUGGING ONLY
void TableOfDebugMoves(std::vector<std::string> &demo_moves){

    const std::string letters = "ABCDEFGHIJ";
    for (int i = 0; i <= 9; ++i) {
        for (int j = 0; j <= 9; ++j) {
            demo_moves.push_back(letters[i] + std::to_string(j));
        }
    }
}
//

int main() {

    srand(static_cast<unsigned int>(time(0)));

    std::array<std::array<int, 10>, 10> field_user{}; //store user main field
    std::array<std::array<int, 10>, 10> field_pc{};   //store pc main field

    std::map<std::string, std::vector<std::pair<int, int>>> map_user{}; //store user ships coords
    std::map<std::string, std::vector<std::pair<int, int>>> map_pc{};   //store pc ships coords

    std::vector<std::pair<int, int>> vec{}; //store coords of where ships can be installed
    std::vector<std::string> pc_moves{}; //store pc moves
    std::vector<std::string> demo_moves{}; //store demo mode moves
        
    std::vector<std::string> ship_name = {"ship4", "ship3_1", "ship3_2", "ship2_1", "ship2_2", "ship2_3", "ship1_1", "ship1_2", "ship1_3", "ship1_4"};

    bool demo {false};
    
    //game loop
    do {
        system(CLS);
        
        map_user.clear();
        map_pc.clear();
        vec.clear();
        pc_moves.clear();
        demo_moves.clear();

        int dir{ 0 };
        createField(field_user);
        createField(field_pc);
        

        if (!isAutomaticSetup(demo)){
            system(CLS);
            std::cout << "\tManual setup\n";
            if (!manualSetup(field_user, field_pc, map_user, ship_name)){
                createGameField(field_user, vec, dir, map_user);
            }
        }else{
            std::cout << "\tAutomatic setup\n";
            createGameField(field_user, vec, dir, map_user);
        }

        system(CLS);
        std::cout << setColor(CColor::Cyan);
        std::cout << "\tGame started!\n";
        std::cout << setColor(CColor::Reset);

        createGameField(field_pc, vec, dir, map_pc);
        createMoveTable(pc_moves);
        

        int row{ 0 }, col{ 0 };
        int pc_row{ 0 }, pc_col{ 0 };

        std::string coord_str = "";
        std::string userLastMove = "";
        std::string pcLastMove = "";
        std::string keyShipHit = ""; //store ship name of the hit ship. it's used in map container
        std::string message_user = "";
        std::string message_pc = "";

        bool isPcHit {false}; //used to check if a move is hit or miss.

        //DEBUGGING
        // if demo mode true
        if(demo) createMoveTable(demo_moves);
        //

        while (1) {

            system(CLS);

            checkField(field_pc);
            checkField(field_user);

            printFields(field_pc, field_user, ShipView::Invisible);
            printUpdateMessage(map_user, map_pc, message_user, message_pc, userLastMove, pcLastMove);

            if (!isPcHit){
                if(!demo){
                    do {
                            std::cout << "  Enter Row and Column (eg. A0 or a0, or 'q' to quit):> ";
                            std::cin >> coord_str;
                            coord_str[0] = std::toupper(coord_str[0]);
                            if (coord_str == "Q") {
                                std::cout << "  See you, bye!\n\n";
                                return 0;
                            }

                    } while (!isInputValid(field_pc, coord_str));
                
                    userLastMove = coord_str;         
                    decodeCoords(coord_str, row, col);

                }else{
                    //if demo mode is chosen
                    getCoord(demo_moves, map_pc, userLastMove, row, col, keyShipHit, Player::User);
                }

                    system(CLS);//COMMENT FOR DEBUG

                    checkField(field_pc);
                    checkField(field_user);

                    //user move
                    if(!isPcHit){//if the previous PC move was not positive then execute User move
                        if (move(field_pc, row, col)) {
                            if (checkMap(map_pc, row, col, field_pc, message_user, keyShipHit, demo_moves, Player::User)) {
                                system(CLS); //COMMENT FOR DEBUG
                                printFields(field_pc, field_user, ShipView::Visible);
                                printCongrats(Player::User);
                                break;
                            }
                            message_pc = "";
                            continue; // continue to next iteration bc User hit positive and move was true
                        }
                        else {
                            message_user = "  You missed at " + userLastMove;
                        }            

                        printFields(field_pc, field_user, ShipView::Invisible);
                        printUpdateMessage(map_user, map_pc, message_user, message_pc, userLastMove, pcLastMove);
                    }

            }


             //pc move
             getCoord(pc_moves, map_user, pcLastMove, pc_row, pc_col, keyShipHit, Player::Pc);
             if (move(field_user, pc_row, pc_col)) {
                 if (checkMap(map_user, pc_row, pc_col, field_user, message_pc, keyShipHit, pc_moves, Player::Pc)) {
                     system(CLS); //COMMENT FOR DEBUG
                     printFields(field_pc, field_user, ShipView::Visible);
                     printCongrats(Player::Pc);
                     break;
                 }
                 message_user = "";
                 isPcHit = true;
            }
             else {
                 message_pc = "   PC missed at " + pcLastMove;
                 isPcHit = false;
            }

            system(CLS);//COMMENT FOR DEBUG
            printFields(field_pc, field_user, ShipView::Invisible);
            printUpdateMessage(map_user, map_pc, message_user, message_pc, userLastMove, pcLastMove);


        }
    } while (playAgain());

    std::cout << std::endl;
    return 0;
}
