#include "field.h"

#ifdef _WIN32
#define CLS "cls"
#define PAUSE "pause"
#endif
#ifdef __APPLE__
#define PAUSE "read"
#define CLS "clear"
#endif

extern int g_TIME;
extern std::string g_VERSION;


std::vector<std::string> ship_name = {"ship4", "ship3_1", "ship3_2", "ship2_1", "ship2_2",
                                        "ship2_3", "ship1_1", "ship1_2", "ship1_3", "ship1_4"};

void Field::sleepThread(int time){
    std::this_thread::sleep_for(std::chrono::milliseconds(time * g_TIME));  
}

int Field::getRandomNumber(int min, int max) {
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

bool Field::inField(int row, int col)
{
    if (row < 0 || row > 9) return false;
    if (col < 0 || col > 9) return false;
    return true;
}


void Field::getPossibles(Field_t const &field,
    std::vector<std::pair<int, int>> &vec, int &dir, int ship) {

    dir = getRandomNumber(0, 1);

    int count{ 0 }, local_row{ 0 }, local_col{ 0 };
    vec.clear();

    if (dir == Direction::Horizontal) {
        //horizontal check
        for (int _row = 0; _row < static_cast<int>(field.size()); ++_row) {
            for (int _col = 0; _col < static_cast<int>(field.size()); ++_col) {
                if (field.at(_row).at(_col) != FieldCellStates::Ship && field.at(_row).at(_col) != FieldCellStates::Border) {
                    if (count == 0) {
                        local_col = _col;
                        local_row = _row;
                    }
                    count++;
                    if (_col == 9 && count < ship) {
                        count = 0;
                    }
                    if (count == ship) {
                        vec.push_back(std::make_pair(local_row, local_col));
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
        for (int _col = 0; _col < static_cast<int>(field.size()); ++_col) {
            for (int _row = 0; _row < static_cast<int>(field.size()); ++_row) {
                if (field.at(_row).at(_col) != FieldCellStates::Ship && field.at(_row).at(_col) != FieldCellStates::Border) {
                    if (count == 0) {
                        local_col = _col;
                        local_row = _row;
                    }
                    count++;
                    if (_row == 9 && count < ship) {
                        count = 0;
                    }
                    if (count == ship) {
                        vec.push_back(std::make_pair(local_row, local_col));
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

void Field::generateFirstShip(Field_t &field, Map_t &map, int const ship, std::string const ship_name) {

    Field::checkField();
    int row{ 0 }, col{ 0 }, dir{ 0 };
    std::vector<std::pair<int, int>> temp_vec;

    do { //iterate while coords are not good enough
        row = Field::getRandomNumber(0, 9);
        col = Field::getRandomNumber(0, 9);
        dir = Field::getRandomNumber(0, 1);

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
    Field::checkField();
}

void Field::setShips(Field_t& field, Map_t& map,
            std::vector<std::pair<int, int>> &vec, int& dir, int ship, std::string ship_name) {

    Field::checkField();
    Field::getPossibles(field, vec, dir, ship);
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
    Field::checkField();
}


void Field::checkHitField() {

    const int y[] = { -1, -1, -1, 1, 1, 1, 0, 0 };// 8 directions
    const int x[] = { -1, 0, 1, -1, 0, 1, -1, 1 };// for checking

    //check in boundary

    for (int row = 0; row < static_cast<int>(field.size()); ++row) {
        for (int col = 0; col <static_cast<int>(field.size()); ++col) {

            if (field.at(row).at(col) == FieldCellStates::Hit) {

                for (int i = 0; i < 8; ++i) { // looking around cell
                    if (Field::inField(row + y[i], col + x[i])) {
                        if (field.at(row + y[i]).at(col + x[i]) != FieldCellStates::Hit && field.at(row + y[i]).at(col + x[i]) != FieldCellStates::Ship)
                            field.at(row + y[i]).at(col + x[i]) = FieldCellStates::BorderHit;
                    }
                }
            }
        }
    }
}

void Field::createField() {
    field.fill({});
}

void Field::printUserField() {

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

void Field::setManualField(std::string coord_str, char dir_char, int ship_size){

    std::vector<std::pair<int, int>> temp_vec;
    int row{0}; int col{0};
    int dir{0};

    Field::decodeCoords(coord_str, row, col);

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
    Field::checkField();
    std::cout << "\tManual setup\n";
    Field::printUserField();

}

bool Field::isManualInputValid(char dir_char){
    if (dir_char == 'v' || dir_char == 'h') 
        return true;
    return false;
}
bool Field::isValidToInstall(int _row, int _col){

    if(field.at(_row).at(_col) == FieldCellStates::Ship || field.at(_row).at(_col) == FieldCellStates::Border){
        printWarning(Warning::TryAgain);
        return false;
    }
    return true;
}

bool Field::isValidToInstall(int _row, int _col, char dir_char, int ship_size){
    
    if ((_row + ship_size) > 10 && (_col + ship_size) > 10){
        Field::printWarning(Warning::TryAgain);
        return false;
    }

    if((_col + ship_size) < 11){
        for (int i = 0; i < ship_size; ++i){
                if(field.at(_row).at(_col + i) == FieldCellStates::Border){
                    continue;
                }
        }
    }
    else if((_row + ship_size) < 11){
        for (int i = 0; i < ship_size; ++i){
                if(field.at(_row + i).at(_col) == FieldCellStates::Border){
                    continue;
                }
        }
    }else{
        Field::printWarning(Warning::TryAgain);
        return false;
    }

    //checking with directions
    if (dir_char == 'v'){
        if ((_row + ship_size) < 11){
                for (int i = 0; i < ship_size; ++i){
                        if(field.at(_row + i).at(_col) == FieldCellStates::Border){
                            Field::printWarning(Warning::TryAgainHorizontal);
                            return false;
                        }
                    }
            }else{
                    Field::printWarning(Warning::TryAgainHorizontal);
                    return false;
                }
    }

    if (dir_char == 'h'){
        if((_col + ship_size) < 11){
                for (int i = 0; i < ship_size; ++i){
                        if(field.at(_row).at(_col + i) == FieldCellStates::Border){
                            Field::printWarning(Warning::TryAgainVertical);
                            return false;
                        }
                    }
            }else{
                Field::printWarning(Warning::TryAgainVertical);
                return false;
                }
        }
    return true;
}


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
Field::Field(){
    createField();
    createGameField();
    createMoveTable();
}

void Field::checkField() {

    const int y[] = { -1, -1, -1, 1, 1, 1, 0, 0 }; // 8 directions
    const int x[] = { -1, 0, 1, -1, 0, 1, -1, 1 }; // for checking
    //check in boundary
    for (int row = 0; row < static_cast<int>(field.size()); ++row) {
        for (int col = 0; col < static_cast<int>(field.size()); ++col) {
            if (field.at(row).at(col) == FieldCellStates::EmptyField) {
                for (int i = 0; i < 8; ++i) { // looking around cell
                    if (Field::inField(row + y[i], col + x[i])) {
                        if (field.at(row + y[i]).at(col + x[i]) == FieldCellStates::Ship)
                            field.at(row).at(col) = FieldCellStates::Border;
                    }
                }
            }
        }
    }
}
void Field::encodeCoords(std::string & _coord_str, int local_row, int local_col) {

    switch (local_row) {
        case 0: _coord_str = "A"; break;
        case 1: _coord_str = "B"; break;
        case 2: _coord_str = "C"; break;
        case 3: _coord_str = "D"; break;
        case 4: _coord_str = "E"; break;
        case 5: _coord_str = "F"; break;
        case 6: _coord_str = "G"; break;
        case 7: _coord_str = "H"; break;
        case 8: _coord_str = "I"; break;
        case 9: _coord_str = "J"; break;
    }

    switch (local_col) {
        case 0: _coord_str += "0"; break;
        case 1: _coord_str += "1"; break;
        case 2: _coord_str += "2"; break;
        case 3: _coord_str += "3"; break;
        case 4: _coord_str += "4"; break;
        case 5: _coord_str += "5"; break;
        case 6: _coord_str += "6"; break;
        case 7: _coord_str += "7"; break;
        case 8: _coord_str += "8"; break;
        case 9: _coord_str += "9"; break;
    }

}

void Field::decodeCoords(const std::string _coord_str, int &_row, int &_col) {

    switch (_coord_str[0]) {
        case 'A': row = 0; _row = 0; break;
        case 'B': row = 1; _row = 1; break;
        case 'C': row = 2; _row = 2; break;
        case 'D': row = 3; _row = 3; break;
        case 'E': row = 4; _row = 4; break;
        case 'F': row = 5; _row = 5; break;
        case 'G': row = 6; _row = 6; break;
        case 'H': row = 7; _row = 7; break;
        case 'I': row = 8; _row = 8; break;
        case 'J': row = 9; _row = 9; break;
    }
    switch (_coord_str[1]) {
        case '0': col = 0; _col = 0; break;
        case '1': col = 1; _col = 1; break;
        case '2': col = 2; _col = 2; break;
        case '3': col = 3; _col = 3; break;
        case '4': col = 4; _col = 4; break;
        case '5': col = 5; _col = 5; break;
        case '6': col = 6; _col = 6; break;
        case '7': col = 7; _col = 7; break;
        case '8': col = 8; _col = 8; break;
        case '9': col = 9; _col = 9; break;
    }
}

void Field::createMoveTable() {

    moves.clear(); //clean before creating

    const std::string letters = "ABCDEFGHIJ";
    for (int i = 0; i <= 9; ++i) {
        for (int j = 0; j <= 9; ++j) {
            moves.push_back(letters[i] + std::to_string(j));
        }
    }
}
void Field::createGameField() {

    Field::createField();
    Field::generateFirstShip(field, map,  ShipType::Carrier, "ship4");
    Field::setShips(field, map, vec, dir, ShipType::Battleship, "ship3_1");
    Field::setShips(field, map, vec, dir, ShipType::Battleship, "ship3_2");
    Field::setShips(field, map, vec, dir, ShipType::Cruiser, "ship2_1");
    Field::setShips(field, map, vec, dir, ShipType::Cruiser, "ship2_2");
    Field::setShips(field, map, vec, dir, ShipType::Cruiser, "ship2_3");
    Field::setShips(field, map, vec, dir, ShipType::Submarine, "ship1_1");
    Field::setShips(field, map, vec, dir, ShipType::Submarine, "ship1_2");
    Field::setShips(field, map, vec, dir, ShipType::Submarine, "ship1_3");
    Field::setShips(field, map, vec, dir, ShipType::Submarine, "ship1_4");
}

//remove PC moves around destroyed ship
void Field::removeMissedMoves() {

    std::string temp_coord = "";
    std::vector<std::string>::iterator it;

    for (int row = 0; row < static_cast<int>(field.size()); ++row) {
        for (int col = 0; col < static_cast<int>(field.size()); ++col) {
            if (field.at(row).at(col) == FieldCellStates::BorderHit) {

                Field::encodeCoords(temp_coord, row, col);

                it = std::find(moves.begin(), moves.end(), temp_coord);
                if (it != moves.end()) {
                    moves.erase(it);
                }
            }
        }
    }
}

//checking which ship is got hit
bool Field::checkMap(Player player) {

    Field::checkField();
    
    std::string temp_coord = "";

    for (auto& [key, value] : map) {

        for (int i = 0; i < static_cast<int>(value.size()); ++i) {
            if (value[i].first == row && value[i].second == col) {
                if (value.size() != 1) {
                    if (player == Player::User){
                        message = "  You hit a ship at " + coord_str;
                        str_keyShipHit = key;
                        lastMove = coord_str;
                        isHit = true;
                        isPartlyHit = true;
                        temp_row = row;
                        temp_col = col;
                    }
                    else {
                        Field::encodeCoords(temp_coord, value[i].first, value[i].second);
                        message = "  PC hit your ship at " + temp_coord;
                        str_keyShipHit = key;
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
                    Field::removeMissedMoves();
                    Field::checkHitField();
                }
                else {
                    message = "  Oops, PC sank your ship!";
                    Field::removeMissedMoves();
                    Field::checkHitField();
                }

                isPartlyHit = false;
                isHit = true;
                temp_coord = key;
            }
        }
    }
    
    if (!temp_coord.empty())
        map.erase(temp_coord);

    if (map.empty()) {
        isHit = false;
        Field::checkField();
        return true;
    }

    Field::checkField();
    return false;
}

void Field::getCoord(Player player) {

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
            Field::sleepThread(150);
            #endif
        }        
        
        // if the previous hit wasn't successful then choose random coord
        if (!isPartlyHit) {

            move = rand() % moves.size();
            lastMove = moves.at(move);
            Field::decodeCoords(lastMove, row, col);

        }

        else {  

            // DEBUGGING
            #if __DEBG
            std::cout << "  temp_row: " << temp_row << " temp_col: " << temp_col << "\n";
            std::cout << ((player == Player::Pc) ? "PC" : "user ") << " map[player.str_keyShipHit].size() = " << map[str_keyShipHit].size() << std::endl;
            #endif

            bool isGoRandom{false};

            // set isGoRandom to true if any ship of 4X-3X-2X gets hit for the first time
            if (map[str_keyShipHit].size() == 3 && str_keyShipHit == "ship4") isGoRandom = true;              //for 4X ship
            if (map[str_keyShipHit].size() == 2 && str_keyShipHit.substr(0, 5) == "ship3") isGoRandom = true; //for 3X ship
            if (map[str_keyShipHit].size() == 1 && str_keyShipHit.substr(0, 5) == "ship2") isGoRandom = true; //for 2X ship


            if (isGoRandom) { //use search for possible coords only for the first time

                for (int i = 0; i < 8; ++i) { // looking around cell
                    if (Field::inField(temp_row + y[i], temp_col + x[i])) {
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

            Field::encodeCoords(temp_pcMove, row, col);

            

            //std::remove_if(pc_moves.begin(), pc_moves.end(), [temp_pcMove](const auto m){ return m == temp_pcMove; }); //using lambda

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
            if (player == Player::Pc) std::cout << "pc ";
            else std::cout << "user ";
            std::cout << str_keyShipHit << " map[player.str_keyShipHit].size() = " << map[str_keyShipHit].size() << "\n";
            system("pause");
        #endif
        //

        if (map[str_keyShipHit].size() == 0){
            isPartlyHit = false;
        }

    }
    #if !(__DEBG)
    Field::sleepThread(450); //600 ms
    #endif
}

bool Field::isInputValid() { //check if user makes correct input

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

        Field::checkField();
        Field::decodeCoords(coord_str, row, col);

        if (field.at(row).at(col) == FieldCellStates::Miss ||
            field.at(row).at(col) == FieldCellStates::BorderHit ||
            field.at(row).at(col) == FieldCellStates::Hit) {
            Field::printWarning(Warning::TryAgainHitThere);
            return false;
        }

        return true;
    }
    else {
        Field::printWarning(Warning::TryAgainWrongCoord);
        return false;
    }
    return false;
}

bool Field::isMove() {

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


bool Field::manualSetup(){

    std::string temp {};
    char dir_char = ' ';
    unsigned int ship_size{0};
    int _row{0}; int _col{0};

    Field::checkField();
    Field::printUserField();
    
    // create bank of ships to be installed - 4X, 3X, 3X, 2X, 2X, 2X, 1X, 1X, 1X, 1X
    std::vector<int> ship_bank = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

    bool switchToAuto = false;

    do {
        
        ship_size = ship_bank[0];

        do {    
            std::cout << setColor(CColor::Cyan);
            std::cout << "  Enter start Row and Column for the ";
            std::cout << setColor(CColor::Yellow);
            std::cout << ship_size << "X";
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
            Field::decodeCoords(coord_str, _row, _col);


            } while (!Field::isInputValid() || !(Field::isValidToInstall(_row, _col, dir_char, ship_size) && Field::isValidToInstall(_row, _col)));

            field.at(_row).at(_col) = FieldCellStates::Ship;
            system(CLS);
            std::cout << "\tManual setup\n";
            Field::printUserField();

        do {
            if(switchToAuto){
                break;
            }

            if (ship_size == 1)
                break;

            std::cout << "  Type 'v' for vertical or 'h' for horizontal placement: ";
            std::cin >> dir_char;
                
            } while (!Field::isManualInputValid(dir_char) || !Field::isValidToInstall(_row, _col, dir_char, ship_size));

        
        Field::setManualField(coord_str, dir_char, ship_size);
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

void Field::clearAll_and_Setup(){
    map.clear();
    moves.clear();
    vec.clear();
    Field::createField();
    Field::createGameField();
    Field::createMoveTable();
}

void Field::printWarning(Warning warning){

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