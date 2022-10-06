//////////////////////////////////////////////////////////////////////////////////////////////
/*
    Battleship game. AU. 09-2022.
    This is a personal challenge project.
    An attempt to recreate the Battleship classic game without looking at other examples.
    The code might look a bit too spaggetti, oh well but it works lol.
*/
/////////////////////////////////////////////////////////////////////////////////////////////

/*
    TODO:
        1. Adjust PC move to make it a bit more random when hitting User's ship.
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

typedef std::map<std::string, std::vector<std::pair<int, int>>> map_t;
typedef std::array<std::array<int, 10>, 10> field_t;
typedef std::vector<std::pair<int, int>> vec_pair_t;

enum Player {
    User,
    Pc
};

enum ShipView {
    Invisible,
    Visible
};

enum Direction {
    Horizontal,
    Vertical
};

enum Ship {

    Submarine = 1,
    Cruiser = 2,
    Battleship = 3,
    Carrier = 4

};

enum FieldCellStates {
    Field,
    Ship,
    Hit,
    Miss,
    BorderHit = 7,
    Border = 8
};

enum Warning{
    TryAgain,
    TryAgainHorizontal,
    TryAgainVertical,
    TryAgainWrongCoord,
    TryAgainHitThere
};

enum ConsoleColor{
    DeepCyan = 3,
    DarkRed = 4,
    NormalWhite = 7,
    Grey = 8,
    Blue = 9,
    Green = 10,
    Red = 12,
    Yellow = 14,
};

int getRandomNumber(int min, int max) {
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void createField(field_t& field) {
    field.fill({ 0,0 });
}

void printUserField(field_t const& field_user) {

    #ifdef _WIN32
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif
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

    for (int row = 0; row < static_cast<int>(field_user.size()); ++row) {
        std::cout << "   " << letters[row] << "  "; //row number

        // user field
        for (int col = 0; col < static_cast<int>(field_user.size()); ++col) {
            if (field_user.at(row).at(col) == FieldCellStates::Ship) {
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, 14); //set console color font green 10, yellow 14, or 22 for selected
                #endif
                std::cout << c_SHIP << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite);
                #endif
            }
            //border around ship
            else if (field_user.at(row).at(col) == FieldCellStates::Border) {
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::Grey); //set console color font green 10, yellow 14
                #endif
                std::cout << c_BORDER << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite);
                #endif
            }
            //ship is hit
            else if (field_user.at(row).at(col) == FieldCellStates::Hit) {
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::Red); //red
                #endif
                std::cout << c_HIT << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite);
                #endif
            }
            //border around hitted ship
            else if (field_user.at(row).at(col) == FieldCellStates::BorderHit) {
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::Blue);
                #endif
                std::cout << c_BORDERHIT << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite);
                #endif
            }
            //missed hit
            else if (field_user.at(row).at(col) == FieldCellStates::Miss) {
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::Blue);
                #endif
                std::cout << c_MISS << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite);
                #endif
            }
            //just empty field
            else {
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::Grey); //set console color font grey 8,
                #endif
                std::cout << c_FIELD << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite);
                #endif
            }
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

//print both fields, make it colorful on windows
void printFields(field_t const& field_pc, field_t const& field_user, ShipView field_view) {

    #ifdef _WIN32
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif
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

    for (int row = 0; row < static_cast<int>(field_user.size()); ++row) {
        std::cout << "   " << letters[row] << "  "; //row number

        // user field
        for (int col = 0; col < static_cast<int>(field_user.size()); ++col) {
            if (field_user.at(row).at(col) == FieldCellStates::Ship) {
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::Yellow); //set console color font green 10, yellow 14, or 22 for selected
                #endif
                std::cout << c_SHIP << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite);
                #endif
            }
            //border around ship
            else if (field_user.at(row).at(col) == FieldCellStates::Border) {
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::Grey); //set console color font green 10, yellow 14
                #endif
                std::cout << c_BORDER << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite);
                #endif
            }
            //ship is hit
            else if (field_user.at(row).at(col) == FieldCellStates::Hit) {
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::Red); //red
                #endif
                std::cout << c_HIT << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite);
                #endif
            }
            //border around hitted ship
            else if (field_user.at(row).at(col) == FieldCellStates::BorderHit) {
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::Blue);
                #endif
                std::cout << c_BORDERHIT << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite);
                #endif
            }
            //missed hit
            else if (field_user.at(row).at(col) == FieldCellStates::Miss) {
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::Blue);
                #endif
                std::cout << c_MISS << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite);
                #endif
            }
            //just empty field
            else {
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::Grey); //set console color font grey 8,
                #endif
                std::cout << c_FIELD << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite);
                #endif
            }
        }

        std::cout << separator;
        std::cout << letters[row] << "  ";

        // pc field
        for (int col = 0; col < static_cast<int>(field_pc.size()); ++col) {
            if (field_pc.at(row).at(col) == FieldCellStates::Ship) {
                #ifdef _WIN32
                //set console color font green 10, yellow 14, 11 light blue, 13 magenta, 9 dark blue or 22 for selected
                SetConsoleTextAttribute(hConsole, ConsoleColor::Grey);
                #endif
                if (field_view == ShipView::Visible)
                    std::cout << c_SHIP << " ";
                else
                    std::cout << c_FIELD << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite);
                #endif
            }
            //border around ship
            else if (field_pc.at(row).at(col) == FieldCellStates::Border) {
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::Grey); //set console color font green 10, yellow 14
                #endif
                std::cout << c_BORDER << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite);
                #endif
            }
            //ship is hit
            else if (field_pc.at(row).at(col) == FieldCellStates::Hit) {
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::Green); //green
                #endif
                std::cout << c_HIT << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite);
                #endif
            }
            //border around hitted ship
            else if (field_pc.at(row).at(col) == FieldCellStates::BorderHit) {
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::DarkRed); //4 dark red
                #endif
                std::cout << c_BORDERHIT << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite);
                #endif
            }
            //missed hit
            else if (field_pc.at(row).at(col) == FieldCellStates::Miss) {
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::DarkRed);
                #endif
                std::cout << c_MISS << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite);
                #endif
            }
            //just empty field
            else {
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::Grey); //set console color font grey 8,
                #endif
                std::cout << c_FIELD << " ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite);
                #endif
            }
        }
        std::cout << std::endl;
    }

    #ifdef _WIN32
    SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite); //set console color font white 7,
    #endif
    std::cout << std::endl;
}

void printUpdateMessage(map_t map_user, map_t map_pc, std::string message_user, std::string message_pc, std::string userLastMove, std::string pcLastMove) {
    std::cout << "       Your ships: " << map_user.size();
    std::cout << "\t\t" << message_user << std::endl;

    std::cout << "         PC ships: " << map_pc.size();
    std::cout << "\t\t" << message_pc << std::endl;

    std::cout << "   Your last move: " << userLastMove << std::endl;
    std::cout << "     PC last move: " << pcLastMove << std::endl;

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
        std::this_thread::sleep_for(std::chrono::milliseconds(25)); //400 ms
    }

    std::cout << std::endl;
}

void startMessage() {

    system(CLS);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    const std::string message_start = "\t\tB A T T L E S H I P  by  AU  1.4";

    for (auto const& letter : message_start) {
        std::cout << letter;
        std::this_thread::sleep_for(std::chrono::milliseconds(25)); //25 ms
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
}

void printWarning(Warning warning){

    #ifdef _WIN32
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, ConsoleColor::DarkRed); //dark red 4
    #endif

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
     #ifdef _WIN32
        SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite); //normal white
    #endif
}

void printMoveTable(std::vector<std::string> const& pc_moves) {
    int a{ 0 };
    for (int i = 0; i < static_cast<int>(pc_moves.size()); ++i) {
        std::cout << pc_moves[i] << " ";
        ++a;
        if (a % 10 == 0) std::cout << std::endl;
    }
    std::cout << std::endl;
}

void printMap(map_t const& map) {

    std::cout << "map size " << map.size() << "\n";

    for (auto& [key, value] : map) {
        std::cout << key << ": ";
        for (int i = 0; i < static_cast<int>(value.size()); ++i) {
            std::cout << value[i].first << "." << value[i].second << " ";
        }
        std::cout << std::endl;
    }
}

bool inField(int row, int col)
{
    if (row < 0 || row > 9) return false;
    if (col < 0 || col > 9) return false;
    return true;
}

//checking field's cells and fill borders around ships
void checkField(field_t& field) {

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

void checkHitField(field_t& field) {

    const int y[] = { -1, -1, -1, 1, 1, 1, 0, 0 };// 8 directions
    const int x[] = { -1, 0, 1, -1, 0, 1, -1, 1 };// for checking

    //check in boundary

    for (int row = 0; row < static_cast<int>(field.size()); ++row) {
        for (int col = 0; col <static_cast<int>(field.size()); ++col) {

            if (field.at(row).at(col) == FieldCellStates::Hit) {

                for (int i = 0; i < 8; ++i) { // looking around cell
                    if (inField(row + y[i], col + x[i])) {
                        if (field.at(row + y[i]).at(col + x[i]) != FieldCellStates::Hit)
                            field.at(row + y[i]).at(col + x[i]) = FieldCellStates::BorderHit;
                    }
                }
            }
        }
    }
}

//making vector of coords possible ships to be setup on field
void getPossibles(field_t const& field, vec_pair_t& vec, int& dir, int ship) {

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

void generateFirstShip(field_t& field, map_t& map, int const ship, std::string const ship_name) {

    checkField(field);
    int row{ 0 }, col{ 0 }, dir{ 0 };
    vec_pair_t temp_vec;

    do { //iterate while coords are not good enough
        row = getRandomNumber(0, 9);
        col = getRandomNumber(0, 9);
        dir = getRandomNumber(0, 1);

    } while (!(field.at(row).at(col) != FieldCellStates::Ship   &&
               field.at(row).at(col) != FieldCellStates::Border &&
               (row + 4) < 9 && (col + 4) < 9));

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
}

void setShips(field_t& field, map_t& map, vec_pair_t& vec, int& dir, int ship, std::string ship_name) {

    checkField(field);
    getPossibles(field, vec, dir, ship);
    vec_pair_t temp_vec;

    int i = rand() % vec.size(); //choose random ship position that can be definitely installed
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
}

void encodeCoords(std::string& coord, int row, int col) {

    switch (row) {
        case 0: coord = "A"; break;
        case 1: coord = "B"; break;
        case 2: coord = "C"; break;
        case 3: coord = "D"; break;
        case 4: coord = "E"; break;
        case 5: coord = "F"; break;
        case 6: coord = "G"; break;
        case 7: coord = "H"; break;
        case 8: coord = "I"; break;
        case 9: coord = "J"; break;
    }

    switch (col) {
        case 0: coord += "0"; break;
        case 1: coord += "1"; break;
        case 2: coord += "2"; break;
        case 3: coord += "3"; break;
        case 4: coord += "4"; break;
        case 5: coord += "5"; break;
        case 6: coord += "6"; break;
        case 7: coord += "7"; break;
        case 8: coord += "8"; break;
        case 9: coord += "9"; break;
    }

}

void decodeCoords(std::string coord, int &row, int &col) {

    switch (coord[0]) {
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
    switch (coord[1]) {
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
void removeMissedMoves(field_t const& field_user, std::vector<std::string>& pc_moves) {

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
bool checkMap(map_t &map, int row, int col, field_t &field, std::string& message, std::string& keyShipHit, std::vector<std::string>& pc_moves, Player player) {

    std::string temp_key = "";

    for (auto& [key, value] : map) {

        for (int i = 0; i < static_cast<int>(value.size()); ++i) {
            if (value[i].first == row && value[i].second == col) {
                if (value.size() != 1) {
                    if (player == Player::User)
                        message = "  You hit a ship!";
                    else {
                        message = "  PC hit your ship!";
                        keyShipHit = key;
                    }
                }
                value.erase(value.begin() + i); //HERE MIGHT BE A PROBLEM!!!
            }

            if (value.empty()) {

                if (player == Player::User) {
                    message = "  Wow! You sank a ship!";
                    checkHitField(field);
                }
                else {
                    message = "  Oops, PC sank your ship!";
                    checkHitField(field);
                    removeMissedMoves(field, pc_moves);
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

void createGameField(field_t& field,
    vec_pair_t& vec, int& dir,
    map_t& map) {

    createField(field);
    generateFirstShip(field, map, Ship::Carrier, "ship4");
    setShips(field, map, vec, dir, Ship::Battleship, "ship3_1");
    setShips(field, map, vec, dir, Ship::Battleship, "ship3_2");
    setShips(field, map, vec, dir, Ship::Cruiser, "ship2_1");
    setShips(field, map, vec, dir, Ship::Cruiser, "ship2_2");
    setShips(field, map, vec, dir, Ship::Cruiser, "ship2_3");
    setShips(field, map, vec, dir, Ship::Submarine, "ship1_1");
    setShips(field, map, vec, dir, Ship::Submarine, "ship1_2");
    setShips(field, map, vec, dir, Ship::Submarine, "ship1_3");
    setShips(field, map, vec, dir, Ship::Submarine, "ship1_4");
    checkField(field);
}

bool isInputValid(field_t& field_pc, std::string& coord) { //check if user makes correct input

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
        coord[1] == '8' || coord[1] == '9')
        && coord.size() == 2) {

        checkField(field_pc);
        int row{ 0 }, col{ 0 };
        decodeCoords(coord, row, col);

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

bool userMove(field_t& field_pc, int row, int col) {

    if (field_pc.at(row).at(col) == FieldCellStates::Ship) {
        field_pc.at(row).at(col) = FieldCellStates::Hit;
        return true;
    }

    else {
        if (field_pc.at(row).at(col) != FieldCellStates::Hit &&
            field_pc.at(row).at(col) != FieldCellStates::Miss) {
            field_pc.at(row).at(col) = FieldCellStates::Miss;
            return false;
        }
        return false;
    }
    return false;
}

void getPcCoord(field_t& field_user, std::vector<std::string>& pc_moves,
    map_t map_user, std::string& pcLastMove,
    int& pc_row, int& pc_col, std::string const& keyShipHit) {

    int move{ 0 };
    std::string temp_pcMove = "";
    std::vector<std::string>::iterator it;

    if (pc_moves.size() > 0) {

        std::cout << "   PC is attacking";
        for (int c = 0; c < 3; ++c) {
            std::cout << ".";
            std::this_thread::sleep_for(std::chrono::milliseconds(250)); //400 ms
        }

        if (map_user[keyShipHit].size() == 0) {

            move = rand() % pc_moves.size();
            pcLastMove = pc_moves.at(move);
            decodeCoords(pcLastMove, pc_row, pc_col);

        }
        else {

            pc_row = map_user[keyShipHit][0].first;
            pc_col = map_user[keyShipHit][0].second;

            encodeCoords(temp_pcMove, pc_row, pc_col);

            it = std::find(pc_moves.begin(), pc_moves.end(), temp_pcMove);

            if (it != pc_moves.end()) {
                move = it - pc_moves.begin();
                pcLastMove = pc_moves.at(move);
            }

        }

        std::cout << " " << pc_moves.at(move) << std::endl;
        pc_moves.erase(pc_moves.begin() + move);

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(600)); //700 ms
}

bool pcMove(field_t& field_user, int row, int col) {

    if (field_user.at(row).at(col) == FieldCellStates::Ship) {
        field_user.at(row).at(col) = FieldCellStates::Hit;
        return true;
    }
    else {
        if (field_user.at(row).at(col) != FieldCellStates::Hit && field_user.at(row).at(col) != FieldCellStates::Miss) {
            field_user.at(row).at(col) = FieldCellStates::Miss;
        }
    }
    return false;
}

void createPcMoveTable(std::vector<std::string>& pc_moves) {

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

        if (exit == 'y') {
            return 1;
            break;
        }
        else if (exit == 'n') {
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

bool isAutomaticSetup(){

    char exit;

    do {
        std::cout << "\n\n";
        std::cout << "        Choose ship setup mode\n\n";
        std::cout << "         'a' for Automatic\n";
        std::cout << "         'm' for Manual\n\n";
        std::cout << "          >: ";
        std::cin >> exit;
        std::cout << std::endl;

        if (exit == 'a') {
            return true;
            break;
        }
        else if (exit == 'm') {
            return false;
            break;
        }
        else {
            system(CLS);
            std::cin.clear(); // 
            std::cin.ignore(32767, '\n');
        }

    } while (1);

    std::cout << std::endl;
}

void setManualField(field_t &field_user, field_t &field_pc, map_t &map_user, std::string coord, char dir_char, int ship, std::vector<std::string> &ship_name){

    vec_pair_t temp_vec;
    int row{0}; int col{0};
    int dir{0};

    decodeCoords(coord, row, col);

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

bool isValidToInstall(field_t &field_user, int row, int col){

    if(field_user.at(row).at(col) == FieldCellStates::Ship || field_user.at(row).at(col) == FieldCellStates::Border){
        printWarning(Warning::TryAgain);
        return false;
       }
    return true;
}

bool isValidToInstall(field_t &field_user, int row, int col, char dir_char, int ship){
    
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

bool manualSetup(field_t &field_user, field_t &field_pc, map_t &map_user, std::vector<std::string> &ship_name){

    std::string coord = "";
    char dir_char = ' ';
    int ship{0};
    int row{0}; int col{0};

    checkField(field_user);
    printUserField(field_user);
    
    // create bank of ships to be installed - 4X, 3X, 3X, 2X, 2X, 2X, 1X, 1X, 1X, 1X
    std::vector<int> ship_bank = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

    #ifdef _WIN32
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif
    bool switchToAuto = false;

    do {
        
        ship = ship_bank[0];

        do {    
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::DeepCyan); //set console color font green 10, yellow 14, or 22 for selected
                #endif
                std::cout << "  Enter start Row and Column for the ";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::Yellow); //set console color font green 10, yellow 14, or 22 for selected
                #endif
                std::cout << ship << "X";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::DeepCyan); //set console color font green 10, yellow 14, or 22 for selected
                #endif
                std::cout << " ship\n";
                #ifdef _WIN32
                SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite); //set console color font green 10, yellow 14, or 22 for selected
                #endif
                std::cout << "  (eg. a0, or type 'auto'): ";
                std::cin >> coord;

                if(coord == "auto"){
                    switchToAuto = true;
                    break;
                }

                coord[0] = std::toupper(coord[0]);
                
                decodeCoords(coord, row, col);


            } while (!isInputValid(field_user, coord) || !(isValidToInstall(field_user, row, col, dir_char, ship) && isValidToInstall(field_user, row, col)));

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

        
        setManualField(field_user, field_pc, map_user, coord, dir_char, ship, ship_name);
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

    startMessage();
    srand(static_cast<unsigned int>(time(0)));

    field_t field_user; //store user main field
    field_t field_pc;   //store pc main field

    map_t map_user; //store user ships coords
    map_t map_pc;   //store pc ships coords

    vec_pair_t vec; //store coords of where ships can be installed
    std::vector<std::string> pc_moves; //store pc moves

    std::vector<std::string> ship_name = {"ship4", "ship3_1", "ship3_2", "ship2_1", "ship2_2", "ship2_3", "ship1_1", "ship1_2", "ship1_3", "ship1_4"};

    //game loop
    do {
        system(CLS);

        map_user.clear();
        map_pc.clear();
        vec.clear();
        pc_moves.clear();

        int dir{ 0 };
        createField(field_user);
        createField(field_pc);

        if (!isAutomaticSetup()){
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
        std::cout << "\tGame started!\n";

        createGameField(field_pc, vec, dir, map_pc);
        createPcMoveTable(pc_moves);
        printFields(field_pc, field_user, ShipView::Invisible);

        int row{ 0 }, col{ 0 };
        int pc_row{ 0 }, pc_col{ 0 };

        std::string coord = "";
        std::string userLastMove = "";
        std::string keyShipHit = "";
        std::string pcLastMove = "";
        std::string message_user = "";
        std::string message_pc = "";

        while (1) {

            do {
                std::cout << "  Enter Row and Column (eg. A0 or a0, or 'q' to quit):> ";
                std::cin >> coord;
                coord[0] = std::toupper(coord[0]);
                if (coord == "Q") {
                    std::cout << "  See you, bye!\n\n";
                    return 0;
                }

            } while (!isInputValid(field_pc, coord));

            system(CLS);

            userLastMove = coord;
            
            decodeCoords(coord, row, col);

            checkField(field_pc);
            checkField(field_user);

            //user move
            if (userMove(field_pc, row, col)) {
                if (checkMap(map_pc, row, col, field_pc, message_user, keyShipHit, pc_moves, Player::User)) {
                    system(CLS);
                    printFields(field_pc, field_user, ShipView::Visible);
                    printCongrats(Player::User);
                    break;
                }
            }
            else {
                message_user = "  You missed.";
            }

            printFields(field_pc, field_user, ShipView::Invisible);
            printUpdateMessage(map_user, map_pc, message_user, message_pc, userLastMove, pcLastMove);

             //pc move
             getPcCoord(field_user, pc_moves, map_user, pcLastMove, pc_row, pc_col, keyShipHit);
             if (pcMove(field_user, pc_row, pc_col)) {
                 if (checkMap(map_user, pc_row, pc_col, field_user, message_pc, keyShipHit, pc_moves, Player::Pc)) {
                     system(CLS);
                     printFields(field_pc, field_user, ShipView::Visible);
                     printCongrats(Player::Pc);
                     break;
                 }
            }
             else {
                 message_pc = "   PC missed.";
            }

            system(CLS);
            printFields(field_pc, field_user, ShipView::Invisible);
            printUpdateMessage(map_user, map_pc, message_user, message_pc, userLastMove, pcLastMove);

        }
        
    } while (playAgain());

    std::cout << std::endl;
    return 0;
}