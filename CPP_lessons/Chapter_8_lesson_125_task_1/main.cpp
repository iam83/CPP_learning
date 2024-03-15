/* 

    1. Напишите класс с именем RGBA, который содержит 4 переменные-члены типа std::uint8_t
    (подключите заголовочный файл cstdint для доступа к типу std::uint8_t):
        m_red
        m_green
        m_blue
        m_alpha

    2. Присвойте 0 в качестве значения по умолчанию для m_red, m_green и m_blue, и 255 для m_alpha.

    3. Создайте конструктор со списком инициализации членов, который позволит пользователю передавать
       значения для m_red, m_green, m_blue и m_alpha.
    
    4. Напишите функцию print(), которая будет выводить значения переменных-членов.

    Подсказка: Если функция print() работает некорректно, то убедитесь, что вы конвертировали std::uint8_t в int.

    Следующий код функции main():
    
        1. int main()
        2. {
        3.      RGBA color(0, 135, 135);
        4.      color.print();
        5.
        6.      return 0;
        7. }
        
    Должен выдавать следующий результат:
    r=0 g=135 b=135 a=255

*/

#include <iostream>
#include <cstdint> // для std::uint8_t

class RGBA{

private:
    std::uint8_t m_red, m_green, m_blue, m_alpha;

public:
    RGBA (std::uint8_t red = 0, std::uint8_t green = 0, std::uint8_t blue = 0, std::uint8_t alpha = 255)
        : m_red(red), m_green(green), m_blue(blue), m_alpha(alpha)
    {
    }

    void print(){
        std::cout << "\n"
                  << " R = " << static_cast<int>(m_red)   << "\n"
                  << " G = " << static_cast<int>(m_green) << "\n"
                  << " B = " << static_cast<int>(m_blue)  << "\n"
                  << " A = " << static_cast<int>(m_alpha) << "\n"
                  << std::endl;
    }
};

int main(){

    RGBA color(0, 135, 135);
    color.print();

    return 0;
}