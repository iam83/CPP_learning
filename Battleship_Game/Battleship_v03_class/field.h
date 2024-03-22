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

    void sleepThread(const int time);
    int getRandomNumber(const int min, const int max);

    bool inField(const int row, const int col);
    void getPossibles(const Field_t &field, std::vector<std::pair<int, int>> &vec, int &dir, const int ship);
    void generateFirstShip(Field_t &field, Map_t &map, const int ship, const std::string ship_name);
    void setShips(Field_t& field, Map_t& map, std::vector<std::pair<int, int>> &vec, int& dir, const int ship, const std::string ship_name);
    void checkHitField();
    void createField();
    void printUserField();
    void setManualField(std::string coord_str, const char dir_char, const int ship_size);

    bool isManualInputValid(const char dir_char);
    bool isValidToInstall(const int _row, const int _col);
    bool isValidToInstall(const int _row, const int _col, const char dir_char, const int ship_size);

    
    std::string m_lastMove = "";
    std::string m_message = "";
    std::string m_str_keyShipHit;


public:

    Field_t field{}; //store user main field
    Map_t map{}; //store user ships coords

    std::vector<std::pair<int, int>> vec{}; //store coords of where ships can be installed
    std::vector<std::string> moves{}; //store pc moves

    std::vector<std::string> ship_name = {"ship4", "ship3_1", "ship3_2", "ship2_1", "ship2_2", "ship2_3", "ship1_1", "ship1_2", "ship1_3", "ship1_4"};

    int row{}, col{};
    size_t temp_row{}, temp_col{};
    int dir{};

    std::string m_coord_str = "";

    bool isHit{};
    bool isPartlyHit{};

    void setLastMove(std::string);
    std::string getLastMove() const;
    void setMessage(std::string _message);
    std::string getMessage() const;

    Field();

    void encodeCoords(std::string & _coord_str, const int local_row, const int local_col);
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