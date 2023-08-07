
#include <iostream>
#include <string>
#include <iomanip>
#include "ccolor.h" // for coloring text in console

//function definition 
double EnterValues(std::string message){

	//проверерям корректность ввода, если будут не INT, то ввод не состоится
	double number = 0;
	do {

        std::cout << setColor(CColor::Cyan);
        std::cout << message;
        std::cout << setColor(CColor::Reset);
        
		std::cin >> number;
        
		if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
        {
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера

            std::cout << setColor(CColor::Red);
            std::cout << "Only numbers please\n" << std::endl;
            std::cout << setColor(CColor::Reset);
        }
        else
        {
            std::cin.ignore(32767,'\n'); // удаляем лишние значения
 			break;
        }

	} while(1);
    
	return number;
}