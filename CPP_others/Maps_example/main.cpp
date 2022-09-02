#include <iostream>
#include <map>
#include <ctime>

// ++i = i+i then cout
// i++ = cout i, then i+i ??

void printMap(const std::map<int, int> &data){
    int i = 0;
    for (auto &pair : data){
        std::cout << i++ << "  --  ";
        std::cout << pair.first << " " << pair.second << std::endl;
    }
    std::cout << "map size: " << data.size() << std::endl << std::endl;
}

int getRandomNumber(int min, int max){
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        return static_cast<int>(rand() * fraction * (max - min + 1) + min);
     }

int main(){

    srand(static_cast<unsigned int>(time(0)));

    std::map<int, int> data;

    for (int i = 0; i <= 5; ++i){
        int temp = getRandomNumber(0, 100);
        int firstValue = temp;
        int secondValue = i;
        data.insert(std::pair<int, int> (firstValue, secondValue));
    }

    printMap(data);
    
    std::cout << "trying to insert into map (0, 38)" << std::endl;
    data.insert(std::pair<int, int>(0, 38));
    printMap(data);

    return 0;
}