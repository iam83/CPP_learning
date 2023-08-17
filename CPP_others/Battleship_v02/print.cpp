#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <thread>
#include <chrono>
#include "ccolor.h"
#include "enums.h"

#ifdef _WIN32
#define CLS "cls"
#endif
#ifdef __APPLE__
#define CLS "clear"
#endif


void printUserField(std::array<std::array<int, 10>, 10> const& field_user) {

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
                std::cout << setColor(CColor::Yellow);
                std::cout << c_SHIP << " ";
                std::cout << setColor(CColor::Reset);
            }
            //border around ship
            else if (field_user.at(row).at(col) == FieldCellStates::Border) {
                std::cout << setColor(CColor::DarkGrey);
                std::cout << c_BORDER << " ";
                std::cout << setColor(CColor::Reset);
            }
            //ship is hit
            else if (field_user.at(row).at(col) == FieldCellStates::Hit) {
                std::cout << setColor(CColor::LightRed);
                std::cout << c_HIT << " ";
                std::cout << setColor(CColor::Reset);
            }
            //border around hitted ship
            else if (field_user.at(row).at(col) == FieldCellStates::BorderHit) {
                std::cout << setColor(CColor::Blue);
                std::cout << c_BORDERHIT << " ";
                std::cout << setColor(CColor::Reset);
            }
            //missed hit
            else if (field_user.at(row).at(col) == FieldCellStates::Miss) {
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

//print both fields, make it colorful on windows
void printFields(std::array<std::array<int, 10>, 10> const& field_pc,
                 std::array<std::array<int, 10>, 10> const& field_user,
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

    for (int row = 0; row < static_cast<int>(field_user.size()); ++row) {
        std::cout << "   " << letters[row] << "  "; //row number

        // user field
        for (int col = 0; col < static_cast<int>(field_user.size()); ++col) {
            if (field_user.at(row).at(col) == FieldCellStates::Ship) {
                std::cout << setColor(CColor::Yellow);
                std::cout << c_SHIP << " ";
                std::cout << setColor(CColor::Reset);
            }
            //border around ship
            else if (field_user.at(row).at(col) == FieldCellStates::Border) {
                std::cout << setColor(CColor::DarkGrey);
                std::cout << c_BORDER << " ";
                std::cout << setColor(CColor::Reset);
            }
            //ship is hit
            else if (field_user.at(row).at(col) == FieldCellStates::Hit) {
                std::cout << setColor(CColor::LightRed);
                std::cout << setColor(CColor::Negative);
                std::cout << c_HIT << " ";
                std::cout << setColor(CColor::Reset);
            }
            //border around hitted ship
            else if (field_user.at(row).at(col) == FieldCellStates::BorderHit) {
                std::cout << setColor(CColor::Blue);
                std::cout << c_BORDERHIT << " ";
                std::cout << setColor(CColor::Reset);
            }
            //missed hit
            else if (field_user.at(row).at(col) == FieldCellStates::Miss) {
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
        for (int col = 0; col < static_cast<int>(field_pc.size()); ++col) {
            if (field_pc.at(row).at(col) == FieldCellStates::Ship) {
                std::cout << setColor(CColor::DarkGrey);
                if (field_view == ShipView::Visible) // make ships visible when game has ended
                    std::cout << c_SHIP << " ";
                else
                    std::cout << c_SHIP << " "; // use c_FIELD for game, use c_SHIP for DEBUGGING
                std::cout << setColor(CColor::Reset);
            }
            //border around ship
            else if (field_pc.at(row).at(col) == FieldCellStates::Border) {
                std::cout << setColor(CColor::DarkGrey);
                std::cout << c_BORDER << " ";
                std::cout << setColor(CColor::Reset);
            }
            //ship is hit
            else if (field_pc.at(row).at(col) == FieldCellStates::Hit) {
                std::cout << setColor(CColor::Green);
                std::cout << setColor(CColor::Negative);
                std::cout << c_HIT << " ";
                std::cout << setColor(CColor::Reset);
            }
            //border around hitted ship
            else if (field_pc.at(row).at(col) == FieldCellStates::BorderHit) {
                std::cout << setColor(CColor::LightRed);
                std::cout << c_BORDERHIT << " ";
                std::cout << setColor(CColor::Reset);
            }
            //missed hit
            else if (field_pc.at(row).at(col) == FieldCellStates::Miss) {
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

void printUpdateMessage(std::map<std::string, std::vector<std::pair<int, int>>> map_user,
                        std::map<std::string, std::vector<std::pair<int, int>>> map_pc,
                        std::string message_user, std::string message_pc,
                        std::string userLastMove, std::string pcLastMove){


    std::cout << "  Your ships left: ";
    if (map_user.size() <= 3)
        std::cout << setColor(CColor::LightRed); //set a color LightRed if ships left <= 3
    std::cout << map_user.size();
    std::cout << setColor(CColor::Reset);

    if (message_user[2] == 'W') //if you sank a ship setColor Green
        std::cout << setColor(CColor::Green);
    if(message_user[6] == 'h') //if you hit a ship setColor Cyan
        std::cout << setColor(CColor::Cyan);

    std::cout << "\t\t" << message_user << std::endl;
    std::cout << setColor(CColor::Reset);

    std::cout << "    PC ships left: ";
    if (map_pc.size() <= 3)
        std::cout << setColor(CColor::LightRed);
    std::cout << map_pc.size();
    std::cout << setColor(CColor::Reset);

    if(message_pc[2] == 'O')
        std::cout << setColor(CColor::Red);
    if(message_pc[5] == 'h')
        std::cout << setColor(CColor::Yellow);
    std::cout << "\t\t" << message_pc << std::endl;
    std::cout << setColor(CColor::Reset);

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

void printMoveTable(std::vector<std::string> const& pc_moves) {
    int a{ 0 };
    for (int i = 0; i < static_cast<int>(pc_moves.size()); ++i) {
        std::cout << pc_moves[i] << " ";
        ++a;
        if (a % 10 == 0) std::cout << std::endl;
    }
    std::cout << std::endl;
}

void printMap(std::map<std::string, std::vector<std::pair<int, int>>> const& map) {

    std::cout << "map size " << map.size() << "\n";
    std::string coord_str = "";

    for (auto& [key, value] : map) {
        std::cout << key << ": ";
        for (int i = 0; i < static_cast<int>(value.size()); ++i) {

            switch (value[i].first) {
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
            std::cout << coord_str << value[i].second << " ";
        }
        std::cout << std::endl;
    }
}