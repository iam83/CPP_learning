#include <iostream>

int boo(){
    return 7;
}

int main(){

    std::cout << reinterpret_cast<void*>(boo) << std::endl;
    return 0;
}