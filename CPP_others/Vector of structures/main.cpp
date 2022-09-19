#include <iostream>
#include <vector>
#include <array>


struct Ship{
    int length;
    std::vector<std::pair<int, int>> coord;
};

int main(){
    
    std::vector<Ship> ships;
    Ship ship4, ship3_1, ship3_2, ship2_1, ship2_2, ship2_3, ship1_1, ship1_2, ship1_3, ship1_4;

    ship4.length = 4;
    ship4.coord = {{5,1}, {5,2}, {5,3}, {5,4}, {5,5}};
    
    ship3_1.length = 3;
    ship3_1.coord = {{3,1}, {3,2}, {3,3}, {3,4}};

    ship3_2.length = 3;
    ship3_2.coord = {{1,1}, {1,2}, {1,3}, {1,4}};

    ships.push_back(ship4);
    ships.push_back(ship3_1);
    ships.push_back(ship3_2);

    int row = 3;
    int col = 3;

    for(int i = 0; i < ships.size(); ++i){
        std::cout << "length " << ships[i].length;
        for (int j = 0; j < ships[i].length; ++j){
                std::cout << " - " << ships[i].coord[j].first << "." << ships[i].coord[j].second << " ";
        }
        std::cout << std::endl;
    }


    for(int i = 0; i < ships.size(); ++i){
        for (int j = 0; j < ships[i].length; ++j){
            if (ships[i].coord[j].first == row && ships[i].coord[j].second == col){
                std::cout << "Found " << row << "." << col << " in ship " << i << " at " << j << std::endl;
                }
            }               
    }

    return 0;
}

