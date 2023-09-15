//////////////////////////////////////////////////////////////////////////////////////////////
/*
    Battleship game. AU. started at 09-2022.

    This is a personal challenge project to learn C++,
    an attempt to recreate the Battleship classic game without looking at other examples,
    methods or ways to implement logic of the game.
    I didn't have to hurry up, so it took awhile to completely get it done.
    The code might look a bit too spaggetti, oh well but it works lol.

    I write this note to myself to make me smile years later :).
    Alright. It took me two weeks to make a working buggy prototype.
    Then I had to put it off for about ~6 months and then finally got back to it
    for fixing and optimizing. It finally works as I planned.

*/
/////////////////////////////////////////////////////////////////////////////////////////////

/*  
    UPDATE:
        29/08/2023 added new mode Help/about. Fixed the issue with choosing coordinates.
        17/08/2023 added Demo mode. PC vs PC. optimized some code
        11/08/2023 updated color output feature to make it cross-platform
*/
/*
    BUGS:
    01. so far so good. no bugs.

*/
/*
    This version is meant to be a test site for optimizing the previous one.
    Next challenge is to wrap it into Classes and Objects.


    TODO (but not so in a hurry):
        1. getCoord - make PC move when it hits the ship but with random coord chosen within possible range
        2. Wrap into a Class
    FEATURES to implement:
        1. As a challenge - try implement Make TCP/IP client-server
*/

#define __DEBG false // set to true to enable DEBUG messages or false to disable.
                     // I'm using this workaround for debugging.
                     // I know it has got some special defines for NDEBUG but I made it simply.

#ifdef _WIN32
#define CLS "cls"
#define PAUSE "pause"
#endif
#ifdef __APPLE__
#define PAUSE "read"
#define CLS "clear"
#endif

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


using Map_t = std::map<std::string, std::vector<std::pair<int, int>>>;
using Field_t = std::array<std::array<int, 10>, 10>;

std::string g_VERSION = "1.9";
int g_TIME = 1; //TIME factor for sleep::thread. Normal is 1 (but for demo mode it will decrease speed for x2) for debug put 0


/**
 * Sleeps the current thread for a specified amount of time.
 * @param time The duration to sleep in milliseconds.
 */
void sleepThread(int time){
    std::this_thread::sleep_for(std::chrono::milliseconds(time * g_TIME));  
}

// struct of boolean states
struct States_b{
    bool isPcHit {false};    //use to check if a move is hit or miss.
    bool isHit {false};      //use to check if a hit happened in getCoord and CheckMap
};


struct PlayerShipHit{

    Player player;
    std::string str_keyShipHit{};   //store ship name which is got hit and use it in map for key
    int temp_row{0}, temp_col{0};

    bool isPartlyHit{};             //use to mark if a ship was partly hit

        PlayerShipHit(Player Player, std::string Str_keyShipHit, bool IsPartlyHit) { 
            player = Player;
            str_keyShipHit = Str_keyShipHit;
            isPartlyHit = IsPartlyHit;
    }
};


//DEBUGGING ONLY
 #if __DEBG
void printDebug(const std::map<std::string, std::vector<std::pair<int, int>>> &map_user,
                const std::map<std::string, std::vector<std::pair<int, int>>> &map_pc,
                const std::vector<std::string> &pc_moves, const States_b states,
                const PlayerShipHit &user, const PlayerShipHit &pc){

        std::cout << "maps_user after pc moves\n";
        printMap(map_user);
        printMoveTable(pc_moves);
        std::cout << std::endl;
        std::cout << "maps_pc after pc moves\n";
        printMap(map_pc);
        std::cout << std::endl;

        std::cout << "isPcHit = " << states.isPcHit << "\n";
        std::cout << "isHit = " << states.isHit << "\n";
        std::cout << "isPartlyHit user = " << user.isPartlyHit << "\n";
        std::cout << "isPartlyHit pc = " << pc.isPartlyHit << "\n";

}
#endif
////


void exit_app(){
    exit(0);
}

int getRandomNumber(int min, int max) {
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void createField(Field_t& field) {
    field.fill({0});
}

/**
 * Checks if the given row and column values are within the valid range.
 *
 * @param row the row value to check
 * @param col the column value to check
 *
 * @return true if the row and column are within the valid range, false otherwise
 */
bool inField(int row, int col)
{
    if (row < 0 || row > 9) return false;
    if (col < 0 || col > 9) return false;
    return true;
}

/**
 * Checks the field for any cells that are surrounded by ships and updates their state to Border.
 * @param field The field to be checked.
 */
void checkField(Field_t &field) {

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

/**
 * Check for hits in the given field and mark neighboring cells as BorderHit if necessary.
 * @param field The field to check for hits and update.
 */
void checkHitField(Field_t& field) {

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
/**
 * Generates the possible positions for a ship on the game field.
 *
 * @param field the game field to search for positions on
 * @param vec a vector to store the possible positions
 * @param dir a reference to the direction variable to set the direction of the ship
 * @param ship_size the length of the ship to find positions for
 */
void getPossibles(Field_t const &field,
    std::vector<std::pair<int, int>> &vec, int &dir, int const ship_size) {

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
                    if (col == 9 && count < ship_size) {
                        count = 0;
                    }
                    if (count == ship_size) {
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
                    if (row == 9 && count < ship_size) {
                        count = 0;
                    }
                    if (count == ship_size) {
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

/**
 * Generates the first ship on the field.
 *
 * @param field the field to generate the ship on
 * @param map the map containing all the ships
 * @param ship the size of the ship to generate
 * @param ship_name the name of the ship
 *
 * @throws ErrorType if an error occurs during ship generation
 */
void generateFirstShip(Field_t &field, Map_t &map, int const ship_size, std::string const ship_name) {

    checkField(field);
    int row{ 0 }, col{ 0 }, dir{ 0 };
    std::vector<std::pair<int, int>> temp_vec;

    do { //iterate while coords are not good enough
        row = getRandomNumber(0, 9);
        col = getRandomNumber(0, 9);
        dir = getRandomNumber(0, 1);

    } while (!(field.at(row).at(col) != FieldCellStates::Ship && field.at(row).at(col) != FieldCellStates::Border && (row + 4) < 9 && (col + 4) < 9));

    if ((col + ship_size) >= 9) col = 4;

    for (int i = 0; i < ship_size; ++i) {
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

void setShips(Field_t& field, Map_t& map,
              std::vector<std::pair<int, int>> &vec, int& dir, int ship, std::string ship_name) {

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

/**
 * Encodes the given coordinates into a string representation.
 *
 * @param coord_str the string to store the encoded coordinates
 * @param row the row coordinate to encode
 * @param col the column coordinate to encode
 */
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

/**
 * Decodes the given coordinate string and assigns the corresponding row and column values.
 *
 * @param coord_str the coordinate string to decode
 * @param row the reference to the variable that will store the decoded row value
 * @param col the reference to the variable that will store the decoded column value
 */
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
bool checkMap(Map_t &map, int row, int col, Field_t &field, std::string &message, PlayerShipHit &player,
              std::vector<std::string> &moves, States_b &states) {

    std::string temp_key = "";

    for (auto& [key, value] : map) {

        for (int i = 0; i < static_cast<int>(value.size()); ++i) {
            if (value[i].first == row && value[i].second == col) {
                if (value.size() != 1) {
                    if (player.player == Player::User){
                        message = "  You hit a ship!";
                        player.str_keyShipHit = key;
                        states.isHit = true;
                        player.isPartlyHit = true;
                        player.temp_row = row;
                        player.temp_col = col;
                    }
                    else {
                        std::string coord_str = "";
                        encodeCoords(coord_str, value[i].first, value[i].second);
                        message = "  PC hit your ship at " + coord_str;
                        player.str_keyShipHit = key;
                        states.isPcHit = true;
                        states.isHit = true;
                        player.isPartlyHit = true;
                        player.temp_row = row;
                        player.temp_col = col;
                    }
                }
                value.erase(value.begin() + i);
            }

            if (value.empty()) { //if all cells from a ship were hit

                if (player.player == Player::User) {
                    message = "  Wow! You sank a ship!";
                    removeMissedMoves(field, moves);
                    checkHitField(field);
                }
                else {
                    message = "  Oops, PC sank your ship!";
                    removeMissedMoves(field, moves);
                    checkHitField(field);
                }

                player.isPartlyHit = false;
                states.isHit = true;
                temp_key = key;
            }
        }
    }
    
    if (!temp_key.empty())
        map.erase(temp_key);

    if (map.empty()) {
        states.isHit = false;
        checkField(field);
        return true;
    }

    checkField(field);
    return false;
}

/**
 * Generates the game field with ships and initializes the map.
 *
 * @param field the game field to be created and populated with ships
 * @param vec a vector of pairs representing the ship coordinates
 * @param dir the direction of the ships (0 for horizontal, 1 for vertical)
 * @param map the map to be initialized
 */
void createGameField(Field_t &field, std::vector<std::pair<int, int>> &vec, int &dir, Map_t &map) {

    createField(field);
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

bool isInputValid(Field_t &field_pc, std::string &coord_str) { //check if user makes correct input

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

bool isMove(Field_t &field, int row, int col) {

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


// get possible coordinates for shooting
void getCoord(std::vector<std::string> &moves, const Field_t &field,
              Map_t map, std::string &lastMove, int &row, int &col,
              PlayerShipHit &player, States_b &states) {

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
        if(player.player == Player::Pc)
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
        if (!player.isPartlyHit) {

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
            if (map[player.str_keyShipHit].size() == 3 && player.str_keyShipHit == "ship4") isGoRandom = true;              //for 4X ship
            if (map[player.str_keyShipHit].size() == 2 && player.str_keyShipHit.substr(0, 5) == "ship3") isGoRandom = true; //for 3X ship
            if (map[player.str_keyShipHit].size() == 1 && player.str_keyShipHit.substr(0, 5) == "ship2") isGoRandom = true; //for 2X ship


            if (isGoRandom) { //use search for possible coords only for the first time

                for (int i = 0; i < 8; ++i) { // looking around cell
                    if (inField(player.temp_row + y[i], player.temp_col + x[i])) {
                        if (field.at(player.temp_row + y[i]).at(player.temp_col + x[i]) != FieldCellStates::Hit &&
                            field.at(player.temp_row + y[i]).at(player.temp_col + x[i]) != FieldCellStates::Miss &&
                            field.at(player.temp_row + y[i]).at(player.temp_col + x[i]) != FieldCellStates::BorderHit){

                                temp_moves.push_back({(player.temp_row + y[i]), (player.temp_col + x[i])}); // if moves are found add them into temp vector

                            }
                    }

                }
            }

            //then if ship is got hit twice so use its exact coordinates to prevent hitting wrong cells otherwise it's dumb.
            //      . . . . x x X. . 
            //
            // for example if a ship is longer than 2 cells then add other possible moves from its coordinates.
            for (size_t i{}; i < map[player.str_keyShipHit].size(); ++i){
                    temp_moves.push_back({map[player.str_keyShipHit][i].first, map[player.str_keyShipHit][i].second}); 
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

        if (map[player.str_keyShipHit].size() == 0){
            player.isPartlyHit = false;
        }

    }
    #if !(__DEBG)
    sleepThread(450); //600 ms
    #endif
}

void createMoveTable(std::vector<std::string> &moves) {

    moves.clear(); //clean before creating

    const std::string letters = "ABCDEFGHIJ";
    for (int i = 0; i <= 9; ++i) {
        for (int j = 0; j <= 9; ++j) {
            moves.push_back(letters[i] + std::to_string(j));
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

void setManualField(Field_t &field_user, Field_t &field_pc,
                    Map_t &map_user, std::string coord_str, char dir_char, int ship, std::vector<std::string> &ship_name){

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

bool isValidToInstall(Field_t &field_user, int row, int col){

    if(field_user.at(row).at(col) == FieldCellStates::Ship || field_user.at(row).at(col) == FieldCellStates::Border){
        printWarning(Warning::TryAgain);
        return false;
       }
    return true;
}

bool isValidToInstall(Field_t &field_user, int row, int col, char dir_char, int ship){
    
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

bool manualSetup(Field_t &field_user, Field_t &field_pc, Map_t &map_user, std::vector<std::string> &ship_name){

    std::string coord_str = "";
    std::string temp {};
    char dir_char = ' ';
    unsigned int ship{0};
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

                if(coord_str[0] == 'q'){
                    std::cout << "See you! Bye.\n\n";
                    exit(0);
                }

                if(coord_str == "auto"){
                    switchToAuto = true;
                    coord_str = "";
                    break;
                }

                for(auto letter : coord_str){
                    temp += std::tolower(letter); //converting string to lowercase
                } 
                coord_str = temp; temp = "";
    

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


int main() {

    srand(static_cast<unsigned int>(time(0)));

    Field_t field_user{}; //store user main field
    Field_t field_pc{};   //store pc main field

    Map_t map_user{}; //store user ships coords
    Map_t map_pc{};   //store pc ships coords

    std::vector<std::pair<int, int>> vec{}; //store coords of where ships can be installed
    std::vector<std::string> pc_moves{}; //store pc moves
    std::vector<std::string> demo_moves{}; //store demo mode moves for user

    // this is for map key. it's used to distinguish ships when they get hit.
    std::vector<std::string> ship_name = {"ship4", "ship3_1", "ship3_2", "ship2_1",
                                          "ship2_2", "ship2_3", "ship1_1", "ship1_2",
                                          "ship1_3", "ship1_4"}; 

    States_b states; //holds boolean states: isHit, isPcHit, isPartlyHit

    bool isDemo {false}; // used to track demo mode enabled/disabled
    
    
    do { //main game loop

        //game setup//
        system(CLS);
        
        map_user.clear();
        map_pc.clear();
        vec.clear();
        pc_moves.clear();
        demo_moves.clear();

        int dir{ 0 };
        createField(field_user);
        createField(field_pc);
        

        
        if (!isAutomaticSetup(isDemo)){
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
        std::string userLastMove = "";  // store user last move and then use it in message system
        std::string pcLastMove = "";    // store PC last move and then use it in message system
        std::string message_user = ""; 
        std::string message_pc = "";

        PlayerShipHit userKeyShipHit(Player::User, "", false); //store ship name of the hit ship. it's used in map container
        PlayerShipHit pcKeyShipHit(Player::Pc, "", false);

        // if demo mode true
        if(isDemo) createMoveTable(demo_moves);
        //

        while (1) {
            
            #if !(__DEBG)
            system(CLS);//COMMENT FOR DEBUGGING
            #endif

            checkField(field_pc);
            checkField(field_user);

            printFields(field_pc, field_user, ShipView::Invisible);
            printUpdateMessage(map_user, map_pc, message_user, message_pc, userLastMove, pcLastMove);
            

            #if __DEBG
            //DEBUGGING
            printDebug(map_user, map_pc, pc_moves, states, userKeyShipHit, pcKeyShipHit);
            #endif

            if (!states.isPcHit){
                if(!isDemo){
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
                    getCoord(demo_moves, field_pc, map_pc, userLastMove, row, col, userKeyShipHit, states);
                }
                    
                    
                    //user move
                    if(!states.isPcHit){//if the previous PC move was not positive then execute User move
                        if (isMove(field_pc, row, col)) {
                            if (checkMap(map_pc, row, col, field_pc, message_user, userKeyShipHit, demo_moves, states)) {

                                #if !(__DEBG)
                                system(CLS); //COMMENT FOR DEBUG
                                #endif

                                printFields(field_pc, field_user, ShipView::Visible);
                                printCongrats(Player::User);
                                break;
                            }
                            message_pc = "";
                            continue; // continue to next iteration bc User hit positive and move was true
                        }
                        else {
                            message_user = "  You missed at " + userLastMove;
                            states.isHit = false;
                        }

                        #if !(__DEBG)
                        system(CLS); //COMMENT FOR DEBUG
                        #endif
                        printFields(field_pc, field_user, ShipView::Invisible);
                        printUpdateMessage(map_user, map_pc, message_user, message_pc, userLastMove, pcLastMove);

                        //DEBUGGING
                        #if __DEBG
                        printDebug(map_user, map_pc, pc_moves, states, userKeyShipHit, pcKeyShipHit);
                        #endif
                    }

            }


             //pc move
             getCoord(pc_moves, field_user, map_user, pcLastMove, pc_row, pc_col, pcKeyShipHit, states);
             if (isMove(field_user, pc_row, pc_col)) {
                 if (checkMap(map_user, pc_row, pc_col, field_user, message_pc, pcKeyShipHit, pc_moves, states)) {
                     #if !(__DEBG)
                     system(CLS); //COMMENT FOR DEBUG
                     #endif

                     printFields(field_pc, field_user, ShipView::Visible);
                     printCongrats(Player::Pc);
                     break;
                 }
                 message_user = "";
                 states.isPcHit = true;
            }
             else {
                 message_pc = "   PC missed at " + pcLastMove;
                 states.isHit = false;
                 states.isPcHit = false;
            }

        }
    } while (playAgain());

    std::cout << std::endl;
    return 0;
}
