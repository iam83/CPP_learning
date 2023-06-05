/* Задание №2
    a) Напишите простой класс с именем Numbers. Этот класс должен иметь:
    - три закрытые переменные-члены типа double: m_a, m_b и m_c;
    - открытый метод с именем setValues(), который позволит устанавливать 
    значения для m_a, m_b и m_c;
    - открытый метод с именем print(), который будет выводить объект класса 
    Numbers в следующем формате: <m_a, m_b, m_c>
*/

#include <iostream>

class Numbers{

    int m_a, m_b, m_c;

public:

    void setValues(int a, int b, int c){
        m_a = a;
        m_b = b;
        m_c = c;
    }

    void print(){
        std::cout << "<" << m_a << ", " << m_b << ", " << m_c << std::endl;
    }

};


int main(){


    return 0;
}