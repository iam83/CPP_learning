#include <iostream>


int main(){

    system("clear");
    while (1){
    int x{80};
    int y{24};

    for (int i=y; i > 0; --i){
        for (int j=x; j > 0; --j){
            if (j==1 || j==80){
                std::cout << "|";
                continue;
            }
            std::cout << "-";
        }

        std::cout << std::endl;
    }
    }

    return 0;
}