#include <iostream>

void printLines(int width, int height, const char symbol){
    for (int i=height; i > 0; --i){
        for (int j=width; j > 0; --j){
            if (j==1 || j==80){
                std::cout << "0";
            }else{
                if (i == 24 || i == 1){
                    std::cout << "0";
                }else{
                     std::cout << symbol;
                    }
            }
        }

        std::cout << std::endl;
    }
}

int main(){

    system("clear");

    int width {80};
    int height {24};
    const char symbol {'-'};
    printLines(width, height, symbol);
    
    return 0;
}