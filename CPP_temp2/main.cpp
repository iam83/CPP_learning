/*

    DEBUGGER TESTS

*/

#include <iostream>
#include <memory>


int main(){

    int a = 8; // create on STACK
    int b = 7;

    //int *p = new int(10); //create on HEAP

    
    auto p = std::make_unique<int>(a + 2);

    return 0;
}