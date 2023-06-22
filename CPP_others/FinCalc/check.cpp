/*

        Colors in OSX Terminal
        
                foreground background
        black        30         40
        red          31         41
        green        32         42
        yellow       33         43
        blue         34         44
        magenta      35         45
        cyan         36         46
        white        37         47


*/




#include <iostream>
#include <string>


#ifdef _WIN32
	#include <windows.h> //for changing color in console
	#include <conio.h> //for getch() function. used for reading key pressing
#endif

#include "enum.h"

//function definition 
double EnterValues(std::string message){

    #ifdef _WIN32
    HANDLE  hConsole;
  	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif

	//проверерям корректность ввода, если будут не INT, то ввод не состоится
	double number = 0;
	do {

        #ifdef _WIN32
        SetConsoleTextAttribute(hConsole, ConsoleColor::DeepCyan); //set console color font bluish
        std::cout << message;
        #endif

        #ifdef __APPLE__
        std::cout << "\033[36m" << message << "\033[0m";
        #endif

        #ifdef _WIN32
        SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite); //set console color font white
        #endif

		std::cin >> number;
        
		if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
        {
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера

            #ifdef _WIN32
            SetConsoleTextAttribute(hConsole, ConsoleColor::Red); //set console color font red
            std::cout << "Only numbers please\n" << std::endl;
            #endif

            #ifdef __APPLE__
            std::cout << "\033[31m" << "Only numbers please\n" << "\033[0m" << std::endl;
            #endif

        }
        else
        {
            std::cin.ignore(32767,'\n'); // удаляем лишние значения
 			break;
        }

	} while(1);
    
	return number;
}