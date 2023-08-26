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
#include "print.h"
#include "ccolor.h"


int g_TIME = 0; //TIME factor for sleep::thread. for demo mode it will x2. for debug put 0

using Map_t = std::map<std::string, std::vector<std::pair<int, int>>>;
using Field_t = std::array<std::array<int, 10>, 10>;


class Field{
    //class for field object
    //it creates, update and keep a field

    struct Ship{
        //struct for ship
        //it stores name, length, vec of coords, direction and maybe some other attributes of a shiop
    };


private:

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


 public:

    Field_t field{}; //store user main field
    Map_t map{}; //store user ships coords

    std::vector<std::pair<int, int>> vec{}; //store coords of where ships can be installed
    std::vector<std::string> pc_moves{}; //store pc moves
    std::vector<std::string> demo_moves{}; //store demo mode moves

    std::vector<std::string> ship_name = {"ship4", "ship3_1", "ship3_2", "ship2_1", "ship2_2",
                                          "ship2_3", "ship1_1", "ship1_2", "ship1_3", "ship1_4"};

    struct States_b{
        bool isPcHit {false};    //use to check if a move is hit or miss.
        bool isHit {false};      //use to check if a hit happened in getCoord and CheckMap
    };


    struct PlayerShipHit{

        Player player;
            std::string str_keyShipHit{};
            int temp_row{0}, temp_col{0};
            //bool firstHit{false};

            bool isPartlyHit{};             //use to mark if a ship was partly hit

                PlayerShipHit(Player Player, std::string Str_keyShipHit, bool IsPartlyHit) { 
                    player = Player;
                    str_keyShipHit = Str_keyShipHit;
                    isPartlyHit = IsPartlyHit;
            }
        };   

    int row{ 0 }, col{ 0 };
    int dir{ 0 };

    std::string coord_str = "";
    std::string userLastMove = "";
    std::string pcLastMove = "";
    //std::string keyShipHit = ""; //store ship name of the hit ship. it's used in map container
    std::string message_user = "";
    std::string message_pc = "";

    //PlayerShipHit userKeyShipHit(Player::User, "", false); //store ship name of the hit ship. it's used in map container



    void createField() {
        field.fill({0});
    }



//checking field's cells and fill borders around ships
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

    //making a vector of possible coordinates where ships can be placed on the field
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
                        checkHitField();
                    }
                    else {
                        message = "  Oops, PC sank your ship!";
                        removeMissedMoves(field, moves);
                        checkHitField();
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
            checkField();
            return true;
        }

        checkField();
        return false;
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

            checkField();
            int row{ 0 }, col{ 0 };
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
                std::cout << "   PC is attacking";
            else
                std::cout << " User is attacking";
                
            for (int c = 0; c < 3; ++c) {
                std::cout << ".";
                sleepThread(150);
            }

            //(map[keyShipHit.pc].size() == 0 && map[keyShipHit.user].size() == 0) ||
            
            
            // if (!states.isHit || !player.isPartlyHit)
            if (!player.isPartlyHit) {

                move = rand() % moves.size();
                lastMove = moves.at(move);
                decodeCoords(lastMove, row, col);

            }

            else {  

                    // DEBUGGING
                    std::cout << "  temp_row: " << player.temp_row << " temp_col: " << player.temp_col << "\n";

                    if (map[player.str_keyShipHit].size() != 1 && map[player.str_keyShipHit].size() != 2) { //use search for possible coords only for the first time

                    // if field cell is marked as hit ship then go and check around for possible moves
                    // if (field.at(row).at(col) == FieldCellStates::Hit)
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

                    // then if ship is hit twice then use its exact coordinates to prevent hitting wrong cells
                    //      . . . . x x X. . 
                    //
                    // for example if a ship is longer than 2 cells then add other possible moves from its coordinates.
                    for (size_t i{}; i < map[player.str_keyShipHit].size(); ++i){
                        temp_moves.push_back({map[player.str_keyShipHit][i].first, map[player.str_keyShipHit][i].second}); 
                        }

                    //DEBUGGING
                    //std::sort( temp_moves.begin(), temp_moves.end() );
                    //temp_moves.erase(std::unique( temp_moves.begin(), temp_moves.end() ), temp_moves.end() );

                    std::cout << "moves before sort ";
                        for (auto const &move : temp_moves){
                            encodeCoords(temp_pcMove, move.first, move.second);
                            std::cout << temp_pcMove[0] << temp_pcMove[1] << " / ";
                        }
                        std::cout << std::endl;
                    //
                    
                    //removes duplicates that are added from above
                    std::sort( temp_moves.begin(), temp_moves.end() );
                    temp_moves.erase(std::unique( temp_moves.begin(), temp_moves.end() ), temp_moves.end() );

                    std::cout << "moves ";
                        for (auto const &move : temp_moves){
                            encodeCoords(temp_pcMove, move.first, move.second);
                            std::cout << temp_pcMove[0] << temp_pcMove[1] << " / ";
                        }
                        std::cout << std::endl;
                        system("pause");

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
                if (player.player == Player::Pc) std::cout << "pc ";
                else std::cout << "user ";
                std::cout << player.str_keyShipHit << " map[player.str_keyShipHit].size() = " << map[player.str_keyShipHit].size() << "\n";
                system("pause");
            //

            if (map[player.str_keyShipHit].size() == 0){
                player.isPartlyHit = false;
            }

        }
        sleepThread(300); //600 ms
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

};


class Game{
    //class for print function etc.
public:
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

};


int main(){

    srand(static_cast<unsigned int>(time(0)));

    Game game;
    Field field_user;
    Field field_pc;

    field_user.createField();
    field_pc.createField();

    field_pc.createGameField();
    field_user.createGameField();

    game.printFields(field_pc, field_user, ShipView::Visible);

    return 0;
}