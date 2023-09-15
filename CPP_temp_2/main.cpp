#include <iostream>
#include <string>
#include <vector>

/*
enum Row{
    Row_A, Row_B, Row_C, Row_D, Row_E, Row_F, Row_G, Row_H, Row_I, Row_J
    };

enum Col{
    Col_0, Col_1, Col_2, Col_3, Col_4, Col_5, Col_6, Col_7, Col_8, Col_9
    };

struct Coord{
    Row row;
    Col col;
    };

struct Ship{

        enum Direction {
        Horizontal,
        Vertical
        };

    enum ShipType {

        Submarine = 1,
        Cruiser = 2,
        Battleship = 3,
        Carrier = 4

        };

    std::string name{};
    ShipType ship_type;
    std::vector<Coord> coord;
    Direction dir;

    Ship(std::string Name, ShipType Ship_type, std::vector<Coord> Coord, Direction Dir){
        name = Name;
        coord = Coord;
        dir = Dir;
        ship_type = Ship_type;
    }

};


void print(Ship &ship){

    std::string shipName{};

    switch(ship.ship_type){
        case Ship::ShipType::Submarine:  shipName = "Submarine"; break;
        case Ship::ShipType::Cruiser:  shipName = "Cruiser"; break;
        case Ship::ShipType::Battleship:  shipName = "Battleship"; break;
        case Ship::ShipType::Carrier:  shipName = "Carrier"; break;
        default: shipName = "Undefined"; break;
    }

    std::cout << "Ship name: " << ship.name << std::endl;
    std::cout << "Ship type: " << shipName << std::endl;
    std::cout << "Ship coord: ";
    for (const auto& c : ship.coord)
        std::cout << " row = " << c.row << " col = " << c.col << " |";
    
    std::cout << std::endl;
    std::cout << "Ship direction: " << (ship.dir == Ship::Direction::Horizontal ? "horizontal" : "vertical") << std::endl;
}


void printAbout(){

    std::cout << "Battleship (also known as Battleships or Sea Battle[1])\nis a strategy type guessing game for two players.\nIt is played on ruled grids (paper or board) on which each player\'s fleet of warships are marked.\nThe locations of the fleets are concealed from the other player.\nPlayers alternate turns calling \"shots\" at the other player\'s ships,\nand the objective of the game is to destroy the opposing player\'s fleet.";

}

int main(){

    std::vector<Coord> coord;
    Coord b, c;
    c.row = Row::Row_A;
    c.col = Col::Col_3;

    b.row = Row::Row_C;
    b.col = Col::Col_2;

    coord.push_back(c);
    coord.push_back(b);

    Ship sub("ship2", Ship::ShipType::Battleship, coord, Ship::Direction::Horizontal);
    std::cout << Ship::ShipType::Carrier << std::endl;
    
    print(sub);


    //test .substr() function
    std::string temp = "ship3_2";
    std::cout << temp.substr(0, 5) << std::endl;

    printAbout();

}













int addTwoNumbers(int value_x, int value_y){
    return value_x + value_y; // функция складывает значения, которые приходят из параметров функции
                              //и возвращаем результат в виде int
}

void printResult(int value_result){
    std::cout << "Result: " << value_result; //функция выводит в консоль/терминал значение,
                                             //которые приходит из параметра value_result
}

int main(){

    int x = 2; // создаем переменную х и присваиваей ей значение 2
    int y = 5; // создаем переменную y и присваиваем ей значение 5
    int result = 0; // создаем переменную result для хранения результата

    result = addTwoNumbers(x, y); // вызываем функцию addTwoNumber и передаем ей в качестве параметров x и y.
                                  // функция вернет значение 9 и присвоет его переменной result.

    printResult(result); // вызываем функцию printResult с параметром result. На экран выведется 9.

    return 0;

}














int addTwoNumbers(int x, int y){
    return x + y;
}

void printResult(int result){
    std::cout << "Result: " << result << std::endl;
}


int main(){

    int x{4}, y{5};
    
    printResult(addTwoNumbers(x, y));

    return 0;

}

*/








void printTwoNumbers(int x, int y){
    std::cout << "x = " << x << "  y = " << y << std::endl;
}


// При передаче параметров по ссылке передается ссылка на объект,
// через которую мы можем манипулировать самим объектом, а не просто его значением,
// сама функция ничего не возвращает

void swapTwoNumbers(int &x, int &y){
    int temp = x; //временно объявляем переменную temp
    x = y;
    y = temp;
}


int main(){

    int x{4}, y{5};

    // выводим перемененные в консоль до вызова функции "поменять местами"
    printTwoNumbers(x, y);

    // меняем местами значения переменных x и y
    swapTwoNumbers(x, y); 

    // выводим пермененные в консоль значения
    // переменных после выполнения функции
    printTwoNumbers(x, y);

    return 0;

}