#include <iostream>

void sum(int &x, int &y){
    std::cout << x+y;
}

int main(){

    int x = 2;
    int y = 3;
    sum(x, y);

    return 0;
}