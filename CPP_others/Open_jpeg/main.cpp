#include <iostream>
#include <fstream>
#include <string>

int main(){

    std::ifstream file;

    file.open("test.png");

    std::string temp;

    if(file.is_open()){
    
        while(!file.eof()){

            file >> temp;
            std::cout << temp << " ";
        }

    }
    else{
        std::cout << "File not found" << std::endl;
        return EXIT_FAILURE;
    }

    

    return 0;
}