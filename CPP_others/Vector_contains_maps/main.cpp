#include <iostream>
#include <map>
#include <ctime>
#include <vector>
#include <iterator>
#include <algorithm>

int g_COUNTER = 1000;

double getRandomNumberDouble(double min, double max){
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        return static_cast<double>((rand() * fraction * (max - min + 1) + min));
     }

int getRandomNumber(int min, int max){
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        return static_cast<int>(rand() * fraction * (max - min + 1) + min);
     }


void fillMap(std::map<int, double> &data){
    for (int i = 0; i <= g_COUNTER; ++i){
        int firstValue = i;
        double secondValue = getRandomNumberDouble(0.01, 0.1);
        data.insert(std::pair<int, double> (firstValue, secondValue));
    }
 }
    
void printMap(std::map<int, double> const &data){
    for (const auto &pair : data){
        std::cout << pair.first << " - " << pair.second << std::endl;
    }
}

void printVectorMap(auto const &vectorMap){
     int count{0};
     for (const auto &item : vectorMap){
        std::cout << "vector " << count++ << std::endl;
        for (const auto &value : item){
            std::cout << "first value: " << value.first << " second value: " << value.second << std::endl;
        }
        std::cout << "\n";
    }
}

void fillVectorMap(auto &vectorMap, auto &data){
    vectorMap.push_back(data);
}

bool compare(std::pair<int, double> const &i, std::pair<int, double> const &j) {
  return i.second < j.second;
}

double findMin(std::vector<std::map<int, double>> const &vectorMap){
    std::pair<int, double> min;
    for (auto const &vec : vectorMap){
        min = (*std::min_element(vec.begin(), vec.end(), compare));
    }
    return static_cast<double>(min.second);
}

int main(){

    srand(static_cast<unsigned int>(time(0)));

    std::vector<std::map<int, double>> vectorMap;
    std::map<int, double> data;

    fillMap(data);

    fillVectorMap(vectorMap, data);
    printVectorMap(vectorMap);

    std::cout << "min value is " << findMin(vectorMap) << std::endl;

    //std::pair<int, double> min = (*std::min_element(data.begin(), data.end(), compare));
    //std::cout << "min value is " << min.second << std::endl;

    return 0;
}

