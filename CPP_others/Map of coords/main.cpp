#include <iostream>
#include <vector>
#include <map>
#include <string>

struct Ship{
    int length;
    std::vector<std::pair<int, int>> coord;
};

int main(){
    
    std::map<std::string, std::vector<std::pair<int, int>>> map;

    map = {  {"ship4", {{4,1}, {4,2}, {4,3}, {4,4}}}, {"ship3_1", {{3,1}, {3,2}, {3,3}}}};

    for (int i = 0; i < 3; ++i){
        map.insert({"ship2_" + std::to_string(i), {{i,2}, {i,3}, {i,4}}});
    }
    
    //std::cout << map["ship4"][0].first << " " << map["ship4"][0].second << std::endl;

    int row = 4;
    int col = 1;

    for(auto& [key, value] : map){
        std::cout << key << " ";
            for (auto &v : value){
                std::cout << v.first << "." << v.second << " ";
            }
        std::cout << "size " << value.size() << std::endl;
        std::cout << std::endl; 
    }

    std::cout << std::endl;
    std::cout << std::endl;

    for(auto& [key, value] : map){
        //std::cout << key << " ";
            for (int i = 0; i<value.size(); ++i){
                if(value[i].first == row && value[i].second == col){
                    std::cout << "Found " << row << "." << col << " in " << key << std::endl;
                    value.erase(value.begin()+i);
                }

                if (value.empty()){
                    std::cout << key << " is empty \n";
                }
            }
    }

    std::cout << std::endl;
    std::cout << "After erasing" << std::endl;

    for(auto& [key, value] : map){
        std::cout << key << " ";
            for (auto &v : value){
                std::cout << v.first << "." << v.second << " ";
            }
        std::cout << "size " << value.size() << std::endl;
        std::cout << std::endl; 
    }

    return 0;
}

