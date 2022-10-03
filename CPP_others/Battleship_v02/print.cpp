#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>

#include "enums.h"

#ifdef _WIN32
#define CLS "cls"
#include <windows.h>
#endif
#ifdef __APPLE__
#define CLS "clear"
#endif


#ifdef _WIN32
#define CLS "cls"
#include <windows.h>
#endif
#ifdef __APPLE__
#define CLS "clear"
#endif

void printUserField(std::array<std::array<int, 10>, 10> const& field_user) {

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
void printFields(std::array<std::array<int, 10>, 10> const& field_pc, std::array<std::array<int, 10>, 10> const& field_user, ShipView field_view) {

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

void printUpdateMessage(std::map<std::string, std::vector<std::pair<int, int>>> map_user, std::map<std::string, std::vector<std::pair<int, int>>> map_pc, std::string message_user, std::string message_pc, std::string userLastMove, std::string pcLastMove) {
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

    const std::string message_start = "\t\tB A T T L E S H I P  by  AU  1.3";

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

void printMap(std::map<std::string, std::vector<std::pair<int, int>>> const& map) {

    std::cout << "map size " << map.size() << "\n";

    for (auto& [key, value] : map) {
        std::cout << key << ": ";
        for (int i = 0; i < static_cast<int>(value.size()); ++i) {
            std::cout << value[i].first << "." << value[i].second << " ";
        }
        std::cout << std::endl;
    }
}