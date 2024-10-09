// from Copilot AI

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int BOARD_SIZE = 10;

enum ShipType { Carrier, Battleship, Cruiser, Submarine, Destroyer };

struct Ship {
    ShipType type;
    int length;
    string name;
    vector<pair<int, int>> coordinates;
};

bool canPlaceShip(const vector<vector<char>>& board, Ship& ship, int startX, int startY, bool horizontal) {
    if (horizontal) {
        if (startX + ship.length > BOARD_SIZE) return false;
        for (int i = 0; i < ship.length; i++) {
            if (board[startY][startX + i] != '.') return false;
        }
    } else {
        if (startY + ship.length > BOARD_SIZE) return false;
        for (int i = 0; i < ship.length; i++) {
            if (board[startY + i][startX] != '.') return false;
        }
    }
    return true;
}

void placeShip(vector<vector<char>>& board, Ship& ship) {
    int startX, startY;
    bool horizontal;
    do {
        startX = rand() % BOARD_SIZE;
        startY = rand() % BOARD_SIZE;
        horizontal = rand() % 2;
    } while (!canPlaceShip(board, ship, startX, startY, horizontal));

    for (int i = 0; i < ship.length; i++) {
        if (horizontal) {
            board[startY][startX + i] = ship.name[0];
            ship.coordinates.push_back(make_pair(startX + i, startY));
        } else {
            board[startY + i][startX] = ship.name[0];
            ship.coordinates.push_back(make_pair(startX, startY + i));
        }
    }
}

int main() {
    srand(time(0));  // Seed the random number generator
    vector<vector<char>> board(BOARD_SIZE, vector<char>(BOARD_SIZE, '.'));
    vector<Ship> ships = {
        { Carrier, 5, "Carrier" },
        { Battleship, 4, "Battleship" },
        { Cruiser, 3, "Cruiser" },
        { Submarine, 3, "Submarine" },
        { Destroyer, 2, "Destroyer" }
    };

    for (auto& ship : ships) {
        placeShip(board, ship);
    }

    for (const auto& row : board) {
        for (const auto& cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }

    return 0;
}
