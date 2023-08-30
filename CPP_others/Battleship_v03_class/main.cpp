
#define __DEBG false // set to true to enable DEBUG messages or false to disable.
                     // I'm using this workaround for debugging.
                     // I know it has got some special defines for NDEBUG but I made it simply.


#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <ctime>
#include <thread>
#include <chrono>
#include <map>
#include <algorithm>
#include "enums.h"
#include "ccolor.h"

#ifdef _WIN32
#define CLS "cls"
#define PAUSE "pause"
#endif
#ifdef __APPLE__
#define PAUSE "read"
#define CLS "clear"
#endif

std::string g_VERSION = "1.9";
int g_TIME = 0; //TIME factor for sleep::thread. Normal is 1 (but for demo mode it will decrease speed for x2) for debug put 0

using Map_t = std::map<std::string, std::vector<std::pair<int, int>>>;
using Field_t = std::array<std::array<int, 10>, 10>;


class Field{
    //class for field object
    //it creates, update and keep a field

private:

    struct Ship{
        //struct for ship
        //it stores name, length, vec of coords, direction and maybe some other attributes of a shiop
    };

    struct PlayerShipHit{

        Player player;
            std::string str_keyShipHit{};
            int temp_row{0}, temp_col{0};

            bool isPartlyHit{};             //use to mark if a ship was partly hit

                PlayerShipHit(Player Player, std::string Str_keyShipHit, bool IsPartlyHit) { 
                    player = Player;
                    str_keyShipHit = Str_keyShipHit;
                    isPartlyHit = IsPartlyHit;
            }
        };   

    struct States_b{
        bool isPcHit {false};    //use to check if a move is hit or miss.
        bool isHit {false};      //use to check if a hit happened in getCoord and CheckMap
    };



    std::vector<std::string> ship_name = {"ship4", "ship3_1", "ship3_2", "ship2_1", "ship2_2",
                                          "ship2_3", "ship1_1", "ship1_2", "ship1_3", "ship1_4"};

    void sleepThread(int time){
        std::this_thread::sleep_for(std::chrono::milliseconds(time * g_TIME));  
    }

    int getRandomNumber(int min, int max) {
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        return static_cast<int>(rand() * fraction * (max - min + 1) + min);
    }

    bool inField(int row, int col)
    {
        if (row < 0 || row > 9) return false;
        if (col < 0 || col > 9) return false;
        return true;
    }



    void getPossibles(Field_t const &field,
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

    void generateFirstShip(Field_t &field, Map_t &map, int const ship, std::string const ship_name) {

        checkField();
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
        checkField();
    }

    void setShips(Field_t& field, Map_t& map,
                std::vector<std::pair<int, int>> &vec, int& dir, int ship, std::string ship_name) {

        checkField();
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
        checkField();
    }


    void checkHitField() {

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

    void createField() {
        field.fill({0});
    }

    void printUserField() {

    std::cout << std::endl;
    const std::string letters = "ABCDEFGHIJ";
    const std::string separator = "        ";
    std::cout << "      ";

    const char c_SHIP = '#';
    const char c_HIT = 'X';
    const char c_MISS = '~';
    const char c_FIELD = '.';
    const char c_BORDER = '.';
    const char c_BORDERHIT = '~';

    for (int c = 0; c < 10; ++c) {
        std::cout << c << " ";
    }

    std::cout << std::endl;

    for (int row = 0; row < static_cast<int>(field.size()); ++row) {
        std::cout << "   " << letters[row] << "  "; //row number
        
        // user field
        for (int col = 0; col < static_cast<int>(field.size()); ++col) {
            if (field.at(row).at(col) == FieldCellStates::Ship) {
                std::cout << setColor(CColor::Yellow);
                std::cout << c_SHIP << " ";
                std::cout << setColor(CColor::Reset);
            }
            //border around ship
            else if (field.at(row).at(col) == FieldCellStates::Border) {
                std::cout << setColor(CColor::DarkGrey);
                std::cout << c_BORDER << " ";
                std::cout << setColor(CColor::Reset);
            }
            //ship is hit
            else if (field.at(row).at(col) == FieldCellStates::Hit) {
                std::cout << setColor(CColor::LightRed);
                std::cout << c_HIT << " ";
                std::cout << setColor(CColor::Reset);
            }
            //border around hitted ship
            else if (field.at(row).at(col) == FieldCellStates::BorderHit) {
                std::cout << setColor(CColor::Blue);
                std::cout << c_BORDERHIT << " ";
                std::cout << setColor(CColor::Reset);
            }
            //missed hit
            else if (field.at(row).at(col) == FieldCellStates::Miss) {
                std::cout << setColor(CColor::Blue);
                std::cout << c_MISS << " ";
                std::cout << setColor(CColor::Reset);
            }
            //just empty field
            else {
                std::cout << setColor(CColor::DarkGrey);
                std::cout << c_FIELD << " ";
                std::cout << setColor(CColor::Reset);
            }
        }

            std::cout << std::endl;
    }

        std::cout << std::endl;
    }

   void setManualField(std::string coord_str, char dir_char, int ship_size){

        std::vector<std::pair<int, int>> temp_vec;
        int row{0}; int col{0};
        int dir{0};

        decodeCoords(coord_str, row, col);

        if (dir_char == 'h')
            dir = Direction::Horizontal;
        else if (dir_char == 'v')
            dir = Direction::Vertical;

        for (int i = 0; i < ship_size; ++i) {
            if (dir == Direction::Horizontal) {
                field.at(row).at(col + i) = FieldCellStates::Ship;
                temp_vec.emplace_back(row, col + i);
            }
            else {
                field.at(row + i).at(col) = FieldCellStates::Ship;
                temp_vec.emplace_back(row + i, col);
            }
        }

        map.emplace(ship_name[0], temp_vec);
        ship_name.erase(ship_name.begin());

        system(CLS);
        checkField();
        std::cout << "\tManual setup\n";
        printUserField();

    }

    bool isManualInputValid(char dir_char){
        if (dir_char == 'v' || dir_char == 'h') 
            return true;
        return false;
    }
    bool isValidToInstall(int row, int col){

        if(field.at(row).at(col) == FieldCellStates::Ship || field.at(row).at(col) == FieldCellStates::Border){
            printWarning(Warning::TryAgain);
            return false;
        }
        return true;
    }

    bool isValidToInstall(int row, int col, char dir_char, int ship){
        
        if ((row + ship) > 10 && (col + ship) > 10){
            printWarning(Warning::TryAgain);
            return false;
        }

        if((col + ship) < 11){
            for (int i = 0; i < ship; ++i){
                    if(field.at(row).at(col + i) == FieldCellStates::Border){
                        continue;
                    }
            }
        }
        else if((row + ship) < 11){
            for (int i = 0; i < ship; ++i){
                    if(field.at(row + i).at(col) == FieldCellStates::Border){
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
                            if(field.at(row + i).at(col) == FieldCellStates::Border){
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
                            if(field.at(row).at(col + i) == FieldCellStates::Border){
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

 public:

    Field_t field{}; //store user main field
    Map_t map{}; //store user ships coords

    std::vector<std::pair<int, int>> vec{}; //store coords of where ships can be installed
    std::vector<std::string> moves{}; //store pc moves

    int row{ 0 }, col{ 0 };
    size_t temp_row{0}, temp_col{0};
    int dir{ 0 };

    std::string coord_str = "";
    std::string lastMove = "";
    std::string message = "";
    std::string str_keyShipHit = "";

    bool isHit{false};
    bool isPartlyHit{false};
    bool isPcHit{false};


    //PlayerShipHit userKeyShipHit(Player::User, "", false); //store ship name of the hit ship. it's used in map container

    //constructor without parameters
    Field(){
        createField();
        createGameField();
        createMoveTable();
    }
    

         void encodeCoords(std::string &coord_str, int row, int col) {

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

    void decodeCoords(const std::string coord_str, const int input_row, const int input_col) {

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
    void checkField() {

        const int y[] = { -1, -1, -1, 1, 1, 1, 0, 0 }; // 8 directions
        const int x[] = { -1, 0, 1, -1, 0, 1, -1, 1 }; // for checking
        //check in boundary
        for (int row = 0; row < static_cast<int>(field.size()); ++row) {
            for (int col = 0; col < static_cast<int>(field.size()); ++col) {
                if (field.at(row).at(col) == FieldCellStates::EmptyField) {
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

    void createMoveTable() {

        moves.clear(); //clean before creating

        const std::string letters = "ABCDEFGHIJ";
        for (int i = 0; i <= 9; ++i) {
            for (int j = 0; j <= 9; ++j) {
                moves.push_back(letters[i] + std::to_string(j));
            }
        }
    }
    void createGameField() {

        createField();
        generateFirstShip(field, map,  ShipType::Carrier, "ship4");
        setShips(field, map, vec, dir, ShipType::Battleship, "ship3_1");
        setShips(field, map, vec, dir, ShipType::Battleship, "ship3_2");
        setShips(field, map, vec, dir, ShipType::Cruiser, "ship2_1");
        setShips(field, map, vec, dir, ShipType::Cruiser, "ship2_2");
        setShips(field, map, vec, dir, ShipType::Cruiser, "ship2_3");
        setShips(field, map, vec, dir, ShipType::Submarine, "ship1_1");
        setShips(field, map, vec, dir, ShipType::Submarine, "ship1_2");
        setShips(field, map, vec, dir, ShipType::Submarine, "ship1_3");
        setShips(field, map, vec, dir, ShipType::Submarine, "ship1_4");
    }
    //remove PC moves around destroyed ship
    void removeMissedMoves(Field_t const &field, std::vector<std::string> &moves) {

        std::string temp_coord = "";
        std::vector<std::string>::iterator it;

        for (int row = 0; row < static_cast<int>(field.size()); ++row) {
            for (int col = 0; col < static_cast<int>(field.size()); ++col) {
                if (field.at(row).at(col) == FieldCellStates::BorderHit) {

                    encodeCoords(temp_coord, row, col);

                    it = std::find(moves.begin(), moves.end(), temp_coord);
                    if (it != moves.end()) {
                        moves.erase(it);
                    }
                }
            }
        }
    }

    //checking which ship is got hit
    bool checkMap(Player player) {

        std::string temp_key = "";

        for (auto& [key, value] : map) {

            for (int i = 0; i < static_cast<int>(value.size()); ++i) {
                if (value[i].first == row && value[i].second == col) {
                    if (value.size() != 1) {
                        if (player == Player::User){
                            message = "  You hit a ship!";
                            str_keyShipHit = key;
                            isHit = true;
                            isPartlyHit = true;
                            temp_row = row;
                            temp_col = col;
                        }
                        else {
                            std::string coord_str = "";
                            encodeCoords(coord_str, value[i].first, value[i].second);
                            message = "  PC hit your ship at " + coord_str;
                            str_keyShipHit = key;
                            isPcHit = true;
                            isHit = true;
                            isPartlyHit = true;
                            temp_row = row;
                            temp_col = col;
                        }
                    }
                    value.erase(value.begin() + i);
                }

                if (value.empty()) { //if all cells from a ship were hit

                    if (player == Player::User) {
                        message = "  Wow! You sank a ship!";
                        removeMissedMoves(field, moves);
                        checkHitField();
                    }
                    else {
                        message = "  Oops, PC sank your ship!";
                        removeMissedMoves(field, moves);
                        checkHitField();
                    }

                    isPartlyHit = false;
                    isHit = true;
                    temp_key = key;
                }
            }
        }
        
        if (!temp_key.empty())
            map.erase(temp_key);

        if (map.empty()) {
            isHit = false;
            checkField();
            return true;
        }

        checkField();
        return false;
    }


    bool isInputValid(std::string &coord_str) { //check if user makes correct input

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

            checkField();
            decodeCoords(coord_str, row, col);

            if (field.at(row).at(col) == FieldCellStates::Miss ||
                field.at(row).at(col) == FieldCellStates::BorderHit ||
                field.at(row).at(col) == FieldCellStates::Hit) {
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

    bool isMove() {

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


    void getCoord(Player player) {

        int move{ 0 };
        std::string temp_pcMove = "";
        std::vector<std::string>::iterator it;

        std::vector<std::pair<int, int>> temp_moves{}; //store temporary moves around the wounded ship
    
        // -1, 0 left
        // +1, 0 right
        // 0, +1 up
        // 0, -1 down
        const int y[] = { -1, 1, 0,  0 };// 4 directions
        const int x[] = {  0, 0, 1, -1 };// for checking

        if (moves.size() > 0) {
            if(player == Player::Pc)
                std::cout << "    PC is attacking";
            else
                std::cout << "  User is attacking";
                
            for (int c = 0; c < 3; ++c) {
                std::cout << ".";

                #if !(__DEBG)
                sleepThread(150);
                #endif
            }        
            
            // if the previous hit wasn't successful then choose random coord
            if (!isPartlyHit) {

                move = rand() % moves.size();
                lastMove = moves.at(move);
                decodeCoords(lastMove, row, col);

            }

            else {  

                // DEBUGGING
                #if __DEBG
                std::cout << "  temp_row: " << player.temp_row << " temp_col: " << player.temp_col << "\n";
                std::cout << ((player.player == Player::Pc) ? "PC" : "user ") << " map[player.str_keyShipHit].size() = " << map[player.str_keyShipHit].size() << std::endl;
                #endif

                bool isGoRandom{false};

                // set isGoRandom to true if any ship of 4X-3X-2X gets hit for the first time
                if (map[str_keyShipHit].size() == 3 && str_keyShipHit == "ship4") isGoRandom = true;              //for 4X ship
                if (map[str_keyShipHit].size() == 2 && str_keyShipHit.substr(0, 5) == "ship3") isGoRandom = true; //for 3X ship
                if (map[str_keyShipHit].size() == 1 && str_keyShipHit.substr(0, 5) == "ship2") isGoRandom = true; //for 2X ship


                if (isGoRandom) { //use search for possible coords only for the first time

                    for (int i = 0; i < 8; ++i) { // looking around cell
                        if (inField(temp_row + y[i], temp_col + x[i])) {
                            if (field.at(temp_row + y[i]).at(temp_col + x[i]) != FieldCellStates::Hit &&
                                field.at(temp_row + y[i]).at(temp_col + x[i]) != FieldCellStates::Miss &&
                                field.at(temp_row + y[i]).at(temp_col + x[i]) != FieldCellStates::BorderHit){

                                    temp_moves.push_back({(temp_row + y[i]), (temp_col + x[i])}); // if moves are found add them into temp vector

                                }
                        }

                    }
                }

                //then if ship is got hit twice so use its exact coordinates to prevent hitting wrong cells otherwise it's dumb.
                //      . . . . x x X. . 
                //
                // for example if a ship is longer than 2 cells then add other possible moves from its coordinates.
                for (size_t i{}; i < map[str_keyShipHit].size(); ++i){
                        temp_moves.push_back({map[str_keyShipHit][i].first, map[str_keyShipHit][i].second}); 
                    }

                //DEBUGGING
                #if __DEBG
                std::cout << "moves before sort ";
                    for (auto const &move : temp_moves){
                        encodeCoords(temp_pcMove, move.first, move.second);
                        std::cout << temp_pcMove[0] << temp_pcMove[1] << " / ";
                    }
                    std::cout << std::endl;
                //
                #endif
                
                //removes duplicates that are added from above
                std::sort( temp_moves.begin(), temp_moves.end() );
                temp_moves.erase(std::unique( temp_moves.begin(), temp_moves.end() ), temp_moves.end() );

                #if __DEBG
                std::cout << "moves ";
                    for (auto const &move : temp_moves){
                        encodeCoords(temp_pcMove, move.first, move.second);
                        std::cout << temp_pcMove[0] << temp_pcMove[1] << " / ";
                    }
                    std::cout << std::endl;
                    system("pause");
                #endif

                int x{};
                if (temp_moves.size() > 1)
                    x = rand() % temp_moves.size(); //then randomly from choose from the temp vector a possible move
                else
                    x = 0;

                if (!temp_moves.empty()){
                    row = temp_moves[x].first; // and apply
                    col = temp_moves[x].second;// both it here
                }
                
                // row = map[keyShipHit][0].first;
                // col = map[keyShipHit][0].second;

                encodeCoords(temp_pcMove, row, col);

                it = std::find(moves.begin(), moves.end(), temp_pcMove);

                if (it != moves.end()) {
                    move = it - moves.begin();
                    lastMove = moves.at(move);
                }

            }

            std::cout << " " << moves.at(move) << std::endl;
            moves.erase(moves.begin() + move);

            //DEBUGGING
            #if __DEBG
                if (player.player == Player::Pc) std::cout << "pc ";
                else std::cout << "user ";
                std::cout << player.str_keyShipHit << " map[player.str_keyShipHit].size() = " << map[player.str_keyShipHit].size() << "\n";
                system("pause");
            #endif
            //

            if (map[str_keyShipHit].size() == 0){
                isPartlyHit = false;
            }

        }
        #if !(__DEBG)
        sleepThread(450); //600 ms
        #endif
    }


    bool manualSetup(){

        std::string coord_str = "";
        std::string temp {};
        char dir_char = ' ';
        unsigned int ship{0};
        int row{0}; int col{0};

        checkField();
        printUserField();
        
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


                } while (!isInputValid(coord_str) || !(isValidToInstall(row, col, dir_char, ship) && isValidToInstall(row, col)));

                field.at(row).at(col) = FieldCellStates::Ship;
                system(CLS);
                std::cout << "\tManual setup\n";
                printUserField();

            do {
                    if(switchToAuto){
                        break;
                    }

                    if (ship == 1)
                        break;
                    std::cout << "  Type 'v' for vertical or 'h' for horizontal placement: ";
                    std::cin >> dir_char;
                    
                } while (!isManualInputValid(dir_char) || !isValidToInstall(row, col, dir_char, ship));

            
            setManualField(coord_str, dir_char, ship);
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

    void clearAll(){
        map.clear();
        moves.clear();
        vec.clear();
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


class Game{
    //class for print function etc.

      void exit_app(){
        exit(0);
    }
public:

    bool isDemo{false};
    
    //DEBUGGING 
    void printMoveTable(Field object) {
        int a{ 0 };
        for (int i = 0; i < static_cast<int>(object.moves.size()); ++i) {
            std::cout << object.moves[i] << " ";
            ++a;
            if (a % 10 == 0) std::cout << std::endl;
        }
        std::cout << std::endl;
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

    void printFields(const Field& field_pc, const Field& field_user,
                    ShipView field_view) {

        std::cout << std::endl;
        const std::string letters = "ABCDEFGHIJ";
        const std::string separator = "        ";
        std::cout << "      ";

        const char c_SHIP = '#';
        const char c_HIT = 'X';
        const char c_MISS = '~';
        const char c_FIELD = '.';
        const char c_BORDER = '.';
        const char c_BORDERHIT = '~';

        for (int c = 0; c < 10; ++c) {
            std::cout << c << " ";
        }

        std::cout << separator << "   ";

        for (int c = 0; c < 10; ++c) {
            std::cout << c << " ";
        }

        std::cout << std::endl;

        for (int row = 0; row < static_cast<int>(field_user.field.size()); ++row) {
            std::cout << "   " << letters[row] << "  "; //row number

            // user field
            for (int col = 0; col < static_cast<int>(field_user.field.size()); ++col) {
                if (field_user.field.at(row).at(col) == FieldCellStates::Ship) {
                    std::cout << setColor(CColor::Yellow);
                    std::cout << c_SHIP << " ";
                    std::cout << setColor(CColor::Reset);
                }
                //border around ship
                else if (field_user.field.at(row).at(col) == FieldCellStates::Border) {
                    std::cout << setColor(CColor::DarkGrey);
                    std::cout << c_BORDER << " ";
                    std::cout << setColor(CColor::Reset);
                }
                //ship is hit
                else if (field_user.field.at(row).at(col) == FieldCellStates::Hit) {
                    std::cout << setColor(CColor::LightRed);
                    std::cout << setColor(CColor::Negative);
                    std::cout << c_HIT << " ";
                    std::cout << setColor(CColor::Reset);
                }
                //border around hitted ship
                else if (field_user.field.at(row).at(col) == FieldCellStates::BorderHit) {
                    std::cout << setColor(CColor::Blue);
                    std::cout << c_BORDERHIT << " ";
                    std::cout << setColor(CColor::Reset);
                }
                //missed hit
                else if (field_user.field.at(row).at(col) == FieldCellStates::Miss) {
                    std::cout << setColor(CColor::Blue);
                    std::cout << c_MISS << " ";
                    std::cout << setColor(CColor::Reset);
                }
                //just empty field
                else {
                    std::cout << setColor(CColor::DarkGrey);
                    std::cout << c_FIELD << " ";
                    std::cout << setColor(CColor::Reset);
                }
            }

            std::cout << separator;
            std::cout << letters[row] << "  ";

            // pc field
            for (int col = 0; col < static_cast<int>(field_pc.field.size()); ++col) {
                if (field_pc.field.at(row).at(col) == FieldCellStates::Ship) {
                    std::cout << setColor(CColor::DarkGrey);
                    if (field_view == ShipView::Visible) // make ships visible when game has ended
                        std::cout << c_SHIP << " ";
                    else
                        std::cout << c_FIELD << " "; // use c_FIELD for game, use c_SHIP for DEBUGGING
                    std::cout << setColor(CColor::Reset);
                }
                //border around ship
                else if (field_pc.field.at(row).at(col) == FieldCellStates::Border) {
                    std::cout << setColor(CColor::DarkGrey);
                    std::cout << c_BORDER << " ";
                    std::cout << setColor(CColor::Reset);
                }
                //ship is hit
                else if (field_pc.field.at(row).at(col) == FieldCellStates::Hit) {
                    std::cout << setColor(CColor::Green);
                    std::cout << setColor(CColor::Negative);
                    std::cout << c_HIT << " ";
                    std::cout << setColor(CColor::Reset);
                }
                //border around hitted ship
                else if (field_pc.field.at(row).at(col) == FieldCellStates::BorderHit) {
                    std::cout << setColor(CColor::LightRed);
                    std::cout << c_BORDERHIT << " ";
                    std::cout << setColor(CColor::Reset);
                }
                //missed hit
                else if (field_pc.field.at(row).at(col) == FieldCellStates::Miss) {
                    std::cout << setColor(CColor::LightRed);
                    std::cout << c_MISS << " ";
                    std::cout << setColor(CColor::Reset);
                }
                //just empty field
                else {
                    std::cout << setColor(CColor::DarkGrey);
                    std::cout << c_FIELD << " ";
                    std::cout << setColor(CColor::Reset);
                }
            }
            std::cout << std::endl;
        }

        std::cout << setColor(CColor::Reset);
        std::cout << std::endl;
    }
    
    bool isAutomaticSetup(bool &isDemo){

        char exit;

        do {
            std::cout << "\n\n\n";
            std::cout << "\t\tB A T T L E S H I P  by  AU  " + g_VERSION;
            std::cout << "\n\n";
            std::cout << "        Choose ship setup mode\n\n";
            std::cout << "         'a' for Automatic\n";
            std::cout << "         'm' for Manual\n";
            std::cout << "         'd' for Demo mode\n";
            std::cout << "         'h' for Help/About\n";
            std::cout << "         'q' for Quit\n\n";
            std::cout << "          >: ";
            std::cin >> exit;
            std::cout << std::endl;
            
            if (exit == 'a' || exit == 'A') {
                std::cin.clear(); // 
                std::cin.ignore(32767, '\n');
                isDemo = false;
                return true;
                break;
            }
            else if (exit == 'm' || exit == 'M') {
                std::cin.clear(); // 
                std::cin.ignore(32767, '\n');
                isDemo = false;
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
                isDemo = {true};
                g_TIME *= 3;
                return true;
            }
                else if (exit == 'h' || exit == 'H') {
                //print about/help message
                system(CLS);
                std::cout << "Battleship (also known as Battleships or Sea Battle)\nis a strategy type guessing game for two players.\n\nIt is played on ruled grids (paper or board) on which each player\'s fleet of warships are marked.\nThe locations of the fleets are concealed from the other player.\nPlayers alternate turns calling \"shots\" at the other player\'s ships,\nand the objective of the game is to destroy the opposing player\'s fleet.\n\n";
                std::cout << "      Automatic - means your ships will be placed automatically.\n";
                std::cout << "      Manual    - means you can decide where and how your ships will be placed.\n";
                std::cout << "      Demo      - means PC vs PC. It's just a demonstration of game play.\n\n";
                std::cout << "Written in C++ by AU as project-based learning in spare time. Thanks for playing.\n";
                std::cout << "Sources can be found on github.com/iam83\n\n";

                #ifdef __APPLE__
                std::cout << "Press Enter to go back...\n"; //this is for mac os x. otherwise it won't print anything.
                #endif

                system(PAUSE);
                system(CLS);

                std::cin.clear(); // 
                std::cin.ignore(32767, '\n');
            }
            else {
                system(CLS);
                std::cin.clear(); // 
                std::cin.ignore(32767, '\n');
            }

        } while (1);

        std::cout << std::endl;
    }


    void printUpdateMessage(const Field &field_pc, const Field & field_user){


        std::cout << "   Your ships left: ";
        if (field_user.map.size() <= 3)
            std::cout << setColor(CColor::LightRed); //set a color LightRed if ships left <= 3
        std::cout << field_user.map.size();
        std::cout << setColor(CColor::Reset);

        if (field_user.message[2] == 'W') //if you sank a ship setColor Green
            std::cout << setColor(CColor::Green);
        if(field_user.message[6] == 'h') //if you hit a ship setColor Cyan
            std::cout << setColor(CColor::Cyan);

        std::cout << "\t\t" << field_user.message << std::endl;
        std::cout << setColor(CColor::Reset);

        std::cout << "     PC ships left: ";
        if (field_pc.map.size() <= 3)
            std::cout << setColor(CColor::LightRed);
        std::cout << field_pc.map.size();
        std::cout << setColor(CColor::Reset);

        if(field_pc.message[2] == 'O')
            std::cout << setColor(CColor::Red);
        if(field_pc.message[5] == 'h')
            std::cout << setColor(CColor::Yellow);
        std::cout << "\t\t" << field_pc.message << std::endl;
        std::cout << setColor(CColor::Reset);

        std::cout << "    Your last move: " << field_user.lastMove << std::endl;
        std::cout << "      PC last move: " << field_pc.lastMove << std::endl;
        
        std::cout << std::endl;
    }

    void printCongrats(Player player) {

        std::string message_congrats = "";

        if (player == Player::User)
            message_congrats = "\t    *** CONGRATULATIONS! YOU WON!!! ***\n";
        else
            message_congrats = "\t             *** YOU LOST!!! ***\n";

        for (auto const& letter : message_congrats) {
            std::cout << letter;
            std::this_thread::sleep_for(std::chrono::milliseconds(25)); //25 ms
        }

        std::cout << std::endl;
    }

};


int main(){

    srand(static_cast<unsigned int>(time(0)));
    std::string coord_str{};

    int input_row{0}, input_col{0};

    Game game;

    Field field_user;
    Field field_pc;

    //game.printFields(field_pc, field_user, ShipView::Visible);

    bool demo {false};
    
    //game loop
    do {

        //game setup//

        system(CLS);

        field_pc.clearAll();
        field_user.clearAll();
        

        if (!game.isAutomaticSetup(demo)){
            system(CLS);
            std::cout << "\tManual setup\n";
            if (!field_user.manualSetup()){
                field_user.createGameField();
            }
        }else{
            std::cout << "\tAutomatic setup\n";
            field_user.createGameField();
        }

        system(CLS);
        std::cout << setColor(CColor::Cyan);
        std::cout << "\tGame started!\n";
        std::cout << setColor(CColor::Reset);

        //DEBUGGING
        // if demo mode true
        if(demo) field_user.createMoveTable();
        //

        while (1) {

            //system(CLS);//COMMENT FOR DEBUGGING
            field_pc.checkField();
            field_user.checkField();

            game.printFields(field_pc, field_user, ShipView::Invisible);
            game.printUpdateMessage(field_pc, field_user);
            
            //DEBUGGING
            //printDebug(map_user, map_pc, pc_moves, states, userKeyShipHit, pcKeyShipHit);

            if (!field_pc.isPcHit){
                if(!demo){
                    do {
                            std::cout << "  Enter Row and Column (eg. A0 or a0, or 'q' to quit):> ";
                            std::cin >> coord_str;
                            coord_str[0] = std::toupper(coord_str[0]);
                            if (coord_str == "Q") {
                                std::cout << "  See you, bye!\n\n";
                                return 0;
                            }

                    } while (!field_user.isInputValid(coord_str));

                }else{
                    //if demo mode is chosen
                    field_user.getCoord(Player::User);
                }

                    //system(CLS);//COMMENT FOR DEBUG

                    //user move
                    if(!field_pc.isPcHit){//if the previous PC move was not positive then execute User move
                        if (field_user.isMove()) {
                            if (field_user.checkMap(Player::User)) {
                                //system(CLS); //COMMENT FOR DEBUG
                                game.printFields(field_pc, field_user, ShipView::Visible);
                                game.printCongrats(Player::User);
                                break;
                            }
                            field_pc.message = "";
                            continue; // continue to next iteration bc User hit positive and move was true
                        }
                        else {
                            field_user.message = "  You missed at " + field_user.lastMove;
                            field_user.isHit = false;
                        }

                        game.printFields(field_pc, field_user, ShipView::Invisible);
                        game.printUpdateMessage(field_pc, field_user);
                        //DEBUGGING
                        //printDebug(map_user, map_pc, pc_moves, states, userKeyShipHit, pcKeyShipHit);
                    }

            }


             //pc move
             field_pc.getCoord(Player::Pc);
             if (field_pc.isMove()) {
                 if (field_pc.checkMap(Player::Pc)) {
                     //system(CLS); //COMMENT FOR DEBUG
                     game.printFields(field_pc, field_user, ShipView::Visible);
                     game.printCongrats(Player::Pc);
                     break;
                 }
                 field_user.message = "";
                 field_pc.isPcHit = true;
            }
             else {
                 field_pc.message = "   PC missed at " + field_pc.message;
                 field_pc.isHit = false;
                 field_pc.isPcHit = false;
            }

            //system(CLS);//COMMENT FOR DEBUG
        }
    } while (game.playAgain());


    return 0;
}