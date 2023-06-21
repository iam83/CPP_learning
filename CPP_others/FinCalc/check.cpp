#include <iostream>
#include <string>
#include <windows.h>

#include "enum.h"

//function definition 
double EnterValues(std::string message){

    HANDLE  hConsole;
  	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//проверерям корректность ввода, если будут не INT, то ввод не состоится
	double number = 0;
	do {

        SetConsoleTextAttribute(hConsole, ConsoleColor::DeepCyan); //set console color font bluish

        std::cout << message;

        SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite); //set console color font white
		std::cin >> number;
        
		if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
        {
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера
            SetConsoleTextAttribute(hConsole, ConsoleColor::Red); //set console color font red
            std::cout << "Only numbers please\n" << std::endl;
        }
        else
        {
            std::cin.ignore(32767,'\n'); // удаляем лишние значения
 			break;
        }

	} while(1);
    
	return number;
}