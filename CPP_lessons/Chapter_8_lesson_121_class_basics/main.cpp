#include <iostream>


class Numbers{

public:
    int m_first;
    int m_second;

    void set(int first, int second){
        m_first = first;
        m_second = second;
    }

    void print(){
        std::cout << "First number: " << m_first << "\n";
        std::cout << "Second number: " << m_second << "\n";
    }

};

int main(){

    Numbers n1; 
    n1.set(3, 5); // инициализируем объект n1 значениями 3 и 3 
    Numbers n2{ 4, 10 }; // инициализируем объект n2 значениями 4 и 4 

    n1.print();
    n2.print(); 

    return 0;
}