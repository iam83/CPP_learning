#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <ctime>


int getRandomNumber(int min, int max){
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        return static_cast<int>(rand() * fraction * (max - min + 1) + min);
     }

void fillIntArr(std::array<std::array<int, 10>, 10> &arr){
    for (int row = 0; row < arr.size(); ++row){
        for (int col = 0; col < arr.size(); ++col){
            arr.at(row).at(col) = getRandomNumber(0, 1);
        }
    }
}

void fillStrArr(std::array<std::array<char, 10>, 10> &arr_str, char sign){
    for (int row = 0; row < arr_str.size(); ++row){
        for (int col = 0; col < arr_str.size(); ++col){
            arr_str.at(row).at(col) = sign;
        }
    }
}

void printStrArr(std::array<std::array<char, 10>, 10> const &arr_str){
     for (int row = 0; row < arr_str.size(); ++row){
        for (int col = 0; col < arr_str.size(); ++col){
            std::cout << arr_str.at(row).at(col);
        }
        std::cout << std::endl;
    }
}

void printIntArr(std::array<std::array<int, 10>, 10> const &arr){
     for (int row = 0; row < arr.size(); ++row){
        for (int col = 0; col < arr.size(); ++col){
            std::cout << arr.at(row).at(col);
        }
        std::cout << std::endl;
    }
}

int main(){

    srand(static_cast<unsigned int>(time(0)));

    std::array<std::array<int, 10>, 10> arr;
    std::array<std::array<char, 10>, 10> arr_str;

    //fillIntArr(arr);
    //printIntArr(arr);

    char sign = '-';
    fillStrArr(arr_str, sign);
    arr_str.at(1).at(2) = '*';
    printStrArr(arr_str);
    
    return 0;
}