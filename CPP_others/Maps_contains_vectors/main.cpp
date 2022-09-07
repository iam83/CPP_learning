#include <iostream>
#include <map>
#include <vector>
#include <ctime> //for srand
#include <algorithm> //sort
#include <fstream>

// ++i = i+i then cout
// i++ = cout i, then i+i ??

double getRandomNumberDouble(int, int);
int getRandomNumber(int, int);
void fillVectorInt(std::vector<int>&);
void fillVectorDouble(std::vector<double>&);
void printVectorInt(const std::vector<int>&);
void printVectorDouble(const std::vector<double>&);
void printMap(std::map<std::vector<int>, std::vector<double>> *p_data, std::ofstream *file);
void printMapRef(std::map<std::vector<int>,std::vector<double>> &data);
void sortVector(std::vector<int>&);
void sortVectorDouble(std::vector<double>&);
void printMapRef_example(std::map<std::vector<int>,std::vector<double>> const &data);


int COUNT = 10;

//typedef std::map<std::vector<int>,std::vector<double>> mapVecIntDouble;

int main(){

    uint16_t startTime = clock();

    std::ofstream file("temp.txt");

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
    //data.insert(std::pair<std::vector<int>, std::vector<double>> (vectorInt2, vectorDouble2));

    printMap(&data, &file); //by pointer
    //printMapRef(data); //by ref
    printMapRef_example(data);

    file.close();

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

void printToFile(auto &data, std::ofstream *file){
    
    if (file->is_open())
            *file << data << " ";
}

void sortVectorDouble(std::vector<double> &vec){
    std::sort(vec.begin(), vec.end());
}

void sortVector(std::vector<int> &vec){
    std::sort(vec.begin(), vec.end());
}

void printMap(std::map<std::vector<int>, std::vector<double>> *p_data, std::ofstream *file){

    for(std::map<std::vector<int>, std::vector<double>>::iterator itr = p_data->begin(); itr != p_data->end(); ++itr){

        for(auto it = itr->first.begin(); it != itr->first.end(); ++it){
                
                std::cout << *it << " ";
                printToFile(*it, file);
            }

        for(auto it2 = itr->second.begin(); it2 != itr->second.end(); ++it2){
                
                std::cout << *it2 << " ";
                printToFile(*it2, file);
            }

       std::cout << std::endl;

    }
}

void printMapRef(std::map<std::vector<int>, std::vector<double>> &data){

    for(std::map<std::vector<int>, std::vector<double>>::iterator itr = data.begin(); itr != data.end(); ++itr){

        std::vector<int> tempVecInt = (*itr).first;
        std::vector<double> tempVecDouble = (*itr).second;

        for (int i = 0; i < tempVecInt.size(); i++){
            std::cout << tempVecInt.at(i) << " ";
        }

        for (int j = 0; j < tempVecDouble.size(); j++){
            std::cout << tempVecDouble.at(j) << " ";
        }

       std::cout << std::endl;

    }
}


void printMapRef_example(std::map<std::vector<int>, std::vector<double>> const &data){
    for(auto& [key, value] : data){
        for (auto &k : key){
            std::cout << k << " " << std::endl;
            }
            for (auto &v : value){
                std::cout << v << " " << std::endl;
                }
    }
}