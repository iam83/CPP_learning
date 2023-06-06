/* 

    Задание №1

    a) Напишите класс Ball, который должен иметь следующие две закрытые 
    переменные-члены со значениями по умолчанию:

    - m_color (Red);
    - m_radius (20.0).

    В классе Ball должны быть следующие конструкторы:

    - для установления значения только для m_color;
    - для установления значения только для m_radius;
    - для установления значений и для m_radius, и для m_color;
    - для установления значений, когда значения не предоставлены вообще.

    Не используйте параметры по умолчанию для конструкторов. Напишите еще одну 
    функцию для вывода цвета (m_color) и радиуса (m_radius) шара (объекта класса Ball).


    Должен выдавать следующий результат:

    color: red, radius: 20
    color: black, radius: 20
    color: red, radius: 30
    color: black, radius: 30


*/

#include <iostream>
#include <string>

class Ball{

private:

    std::string m_color;
    double m_radius;
    
public:

    Ball(double radius){
        m_color = "red";
        m_radius = radius;
    }

    Ball(const std::string &color = "red", double radius = 20.0){
        m_color = color;
        m_radius = radius;
    }

    void print(){
        std::cout << "color: " << m_color << ", radius: " << m_radius << std::endl;
    }

};

int main(){
    
    Ball def; 
    def.print(); 

    Ball black("black"); 
    black.print(); 

    Ball thirty(30.0);
    thirty.print(); 
    
    Ball blackThirty("black", 30.0); 
    blackThirty.print(); 


    return 0;
}