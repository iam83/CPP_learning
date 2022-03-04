#include <iostream>
#include <string>
#include <sstream> //for std::stringstream 


void printFormatAddress(int& ref) {

    const void* address = static_cast<const void*>(&ref);

    std::stringstream ss;
    ss << address;
    std::string name = ss.str();

    for (int i = 0; i < name.size(); i++) {
        std::cout << name[i];
        if (i % 2) std::cout << " ";
    }
}

int main()
{
    int a = 7;
    std::cout << std::endl << std::endl;

    std::cout << "this is value of int a=7: " << a << '\n'; // выводим значение переменной a
    //std::cout << "this is the address of a: " << &a << '\n'; // выводим адрес памяти переменной a

    //выводим отформатированный адрес переменной с пробелами, типа FF FF FF FF FF FF
    std::cout << "this is the address of a: ";
    printFormatAddress(a);
    std::cout << std::endl;

    std::cout << "this is value of &a taken by '*': " << *&a << "\n";
    
    

    return 0;
}