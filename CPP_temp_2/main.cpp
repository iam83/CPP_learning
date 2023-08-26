#include <iostream>


int main(){


    int x{0};

    for(;;){
        std::cout << x << std::endl;
        x++;
        if ( x > 1) std::cout << "x > " << x << " = " << x << std::endl;

        if (x > 10) break;
    }


}