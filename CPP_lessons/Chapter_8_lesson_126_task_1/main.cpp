/* 

    Задание №1
Добавьте в следующую программу инициализацию нестатических членов и список 
инициализации членов:

        Результат выполнения программы должен быть следующим:

        color: blue and radius: 20
        color: red and radius: 20
        color: blue and radius: 30
        color: red and radius: 30

*/

#include <string> 
#include <iostream> 

class Thing{ 
private:

    std::string m_color; 
    double m_radius; 

public: 

    // Конструктор по умолчанию без параметров 
    Thing(){ 
        m_color = "blue"; 
        m_radius = 20.0; 
    } 

    // Конструктор с параметром color (для radius предоставлено значение умолчанию) 
    Thing(const std::string &color){ 
        m_color = color; 
        m_radius = 20.0; 
    } 

    // Конструктор с параметром radius (для color предоставлено значение умолчанию) 
    Thing(double radius){ 
        m_color = "blue"; 
        m_radius = radius; 
    } 

    // Конструктор с параметрами color и radius 
    Thing(const std::string &color, double radius){ 
        m_color = color; 
        m_radius = radius; 
    } 

    void print(){ 
        std::cout << "color: " << m_color << " and radius: " << m_radius << std::endl;
    } 
}; 

int main() 
{ 
    Thing defl; 
    defl.print(); 

    Thing red("red"); 
    red.print(); 

    Thing thirty(30.0); 
    thirty.print(); 

    Thing redThirty("red", 30.0); 
    redThirty.print(); 

    return 0; 
} 