#include <iostream>
#include <string>
#include <windows.h>

//function definition 

double EnterValues(int option){

    HANDLE  hConsole;
  	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//проверерям корректность ввода, если будут не DOUBLE, то ввод не состоится
    int count{0};
	double number = 0;
	do {

        SetConsoleTextAttribute(hConsole, 3); //set console color font bluish

        if (option == 0) // check which message to show
		    std::cout << "Enter time per frame in seconds: ";
        else
            std::cout << "Enter frame amount: ";

        SetConsoleTextAttribute(hConsole, 7); //set console color font white
		std::cin >> number;

		if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
        {
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера
            SetConsoleTextAttribute(hConsole, 12); //set console color font red
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