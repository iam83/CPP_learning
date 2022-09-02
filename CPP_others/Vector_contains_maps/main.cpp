#include <iostream>
#include <map>
#include <ctime>
#include <vector>


double getRandomNumberDouble(double min, double max){
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        return static_cast<double>((rand() * fraction * (max - min + 1) + min));
     }

int getRandomNumber(int min, int max){
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        return static_cast<int>(rand() * fraction * (max - min + 1) + min);
     }


void fillMap(std::map<int, double> &data){

    for (int i = 0; i <= 5; ++i){
        int firstValue = i;
        double secondValue = getRandomNumberDouble(0.01, 0.1);
        data.insert(std::pair<int, double> (firstValue, secondValue));
    }
 }
    
void printMap(const std::map<int, double> &data){

    for (const auto &pair : data){
        std::cout << pair.first << " - " << pair.second << std::endl;
    }

}

int main(){

    srand(static_cast<unsigned int>(time(0)));

    std::vector<std::map<int, double>> vectorMap;
    std::map<int, double> data;

    fillMap(data);
    printMap(data);

    vectorMap.push_back(data);

    for (const auto &item : vectorMap){
        
    }

    return 0;
}

