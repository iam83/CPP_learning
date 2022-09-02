#include <iostream>
#include <map>
#include <vector>
#include <ctime> //for srand
#include <algorithm> //sort
#include <fstream>

// ++i = i+i then cout
// i++ = cout i, then i+i ??

int COUNT = 1000000;

double getRandomNumberDouble(int, int);
int getRandomNumber(int, int);
void fillVectorInt(std::vector<int>&);
void fillVectorDouble(std::vector<double>&);
void printVectorInt(const std::vector<int>&);
void printVectorDouble(const std::vector<double>&);
void printMap(std::map<std::vector<int>, std::vector<double>> *p_data);
void printMapStraight(std::map<std::vector<int>,std::vector<double>> &data);
void sortVector(std::vector<int>&);
void sortVectorDouble(std::vector<double>&);


int main(){

    uint16_t startTime = clock();

    srand(static_cast<unsigned int>(time(0)));

    std::vector<int> vectorInt, vectorInt2;
    std::vector<double> vectorDouble, vectorDouble2;
    std::map<std::vector<int>, std::vector<double>> data;

    fillVectorInt(vectorInt);
    fillVectorInt(vectorInt2);

    
    fillVectorDouble(vectorDouble);
    fillVectorDouble(vectorDouble2);
    
    //sortVector(vectorInt);
    sortVectorDouble(vectorDouble);
    
    data.insert(std::pair<std::vector<int>, std::vector<double>> (vectorInt, vectorDouble));
    data.insert(std::pair<std::vector<int>, std::vector<double>> (vectorInt2, vectorDouble2));

    
    std::map<std::vector<int>, std::vector<double>> * p_data;
    p_data = &data;

    //printMap(&data); //by pointer
    printMapStraight(data); //by ref

    uint16_t sortingTime = clock() - startTime;

	std::cout << "\n\nDone!\n" <<
        "Time: " << sortingTime << " ms.\n\n";

    return 0;
}


double getRandomNumberDouble(double min, double max){
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        return static_cast<double>((rand() * fraction * (max - min + 1) + min));
     }

int getRandomNumber(int min, int max){
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        return static_cast<int>(rand() * fraction * (max - min + 1) + min);
     }


void printMap(const std::map<int, int> &data){

    std::cout << "map size: " << data.size() << std::endl << std::endl;
}

void fillVectorInt(std::vector<int> &vec){
    for(int i = 0; i <= COUNT; ++i){
        vec.push_back(getRandomNumber(0, 10));
    }
}

void fillVectorDouble(std::vector<double> &vec){
        for(int i = 0; i <= COUNT; ++i){
            vec.push_back(getRandomNumberDouble(0.01, 0.1));
        }
}

void printVectorInt(const std::vector<int> &vec){
    for (const auto &value : vec){
        std::cout << "Vector int: " << value << std::endl;
    }
}

void printVectorDouble(const std::vector<double> &vec){
    for (const auto &value : vec){
        std::cout << "Vector double: " << value << std::endl;
    }
}

void printMap(std::map<std::vector<int>, std::vector<double>> *p_data){
    //std::ofstream file("temp.txt");

    for(std::map<std::vector<int>, std::vector<double>>::iterator itr = p_data->begin(); itr != p_data->end(); ++itr){

        for(auto it = itr->first.begin(); it != itr->first.end(); ++it){
                //if (file.is_open()) file << *it << " ";
                std::cout << *it << std::endl;
            }

        for(auto it2 = itr->second.begin(); it2 != itr->second.end(); ++it2){
            //if (file.is_open()) file << *it2 << " ";
                std::cout << *it2 << std::endl;
            }

       std::cout << std::endl;
       //file.close();

    }
}

void printMapStraight(std::map<std::vector<int>,std::vector<double>> &data){
    for(std::map<std::vector<int>, std::vector<double>>::iterator itr = data.begin(); itr != data.end(); ++itr){

        std::vector<int> tempVecInt = (*itr).first;
        std::vector<double> tempVecDouble = (*itr).second;

        for (int i = 0; i < tempVecInt.size(); i++){
            std::cout << tempVecInt.at(i) << std::endl;
        }

        for (int j = 0; j < tempVecDouble.size(); j++){
            std::cout << tempVecDouble.at(j) << std::endl;
        }

       std::cout << std::endl;

    }
}

void sortVectorDouble(std::vector<double> &vec){
    std::sort(vec.begin(), vec.end());
}

void sortVector(std::vector<int> &vec){
    std::sort(vec.begin(), vec.end());
}
