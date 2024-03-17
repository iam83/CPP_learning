#pragma once
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

using Map_t = std::map<std::string, std::vector<std::pair<int, int>>>;
using Field_t = std::array<std::array<int, 10>, 10>;

class Field{

private:

    void sleepThread(int time);
    int getRandomNumber(int min, int max);

    bool inField(int row, int col);
    void getPossibles(Field_t const &field, std::vector<std::pair<int, int>> &vec, int &dir, int ship);
    void generateFirstShip(Field_t &field, Map_t &map, int const ship, std::string const ship_name);
    void setShips(Field_t& field, Map_t& map, std::vector<std::pair<int, int>> &vec, int& dir, int ship, std::string ship_name);
    void checkHitField();
    void createField();
    void printUserField();
    void setManualField(std::string coord_str, char dir_char, int ship_size);

    bool isManualInputValid(const char dir_char);
    bool isValidToInstall(int _row, int _col);
    bool isValidToInstall(int _row, int _col, char dir_char, int ship_size);


public:

    Field_t field{}; //store user main field
    Map_t map{}; //store user ships coords

    std::vector<std::pair<int, int>> vec{}; //store coords of where ships can be installed
    std::vector<std::string> moves{}; //store pc moves

    std::vector<std::string> ship_name = {"ship4", "ship3_1", "ship3_2", "ship2_1", "ship2_2", "ship2_3", "ship1_1", "ship1_2", "ship1_3", "ship1_4"};

    int row{}, col{};
    size_t temp_row{}, temp_col{};
    int dir{};

    std::string coord_str;
    std::string lastMove;
    std::string message;
    std::string str_keyShipHit;

    bool isHit{};
    bool isPartlyHit{};

    Field();

    void encodeCoords(std::string & _coord_str, int local_row, int local_col);
    void decodeCoords(const std::string coord_str, int &_row, int &_col);
    void checkField();
    void createMoveTable();
    void createGameField();
    void removeMissedMoves();
    
    bool checkMap(Player);
    bool isInputValid();
    bool isMove();
    void getCoord(Player);

    bool manualSetup();
    void clearAll();
    
    void printWarning(Warning);

};