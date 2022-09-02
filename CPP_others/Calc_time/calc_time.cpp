/*
	this program calculates total render time
*/

#include <iostream>
#include <iomanip>
#ifdef _WIN32
	#include <windows.h> //for changing color in console
	#include <conio.h> //for getch() function. used for reading key pressing
#endif
#include "check.h" //my header file. splitted for learning purpose. used for checking inputs.


void PrintResult(int time, int frameAmount){
	
	int min_overall = (time*frameAmount)/60.0f;
	int hour = min_overall / 60;
	int min = min_overall % 60;
	int days{0};

	HANDLE  hConsole;
  	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << std::fixed << std::showpoint;
	std::cout << std::setprecision(1); //amount of digits of floating numbers

	//std::cout << std::endl;
	SetConsoleTextAttribute(hConsole, 13); //set console color purple
	std::cout << "Approximate render time: ";

	if (hour > 24){

		
		days = std::abs(hour / 24);
		hour = hour % 24;

		SetConsoleTextAttribute(hConsole, 10); //set console color font green
		std::cout << days;

		SetConsoleTextAttribute(hConsole, 7); //set console color font white
		std::cout << " day(s) ";
	}

	SetConsoleTextAttribute(hConsole, 10); //set console color font green
	std::cout << std::abs(hour);

	SetConsoleTextAttribute(hConsole, 7); //set console color font white
	std::cout << " hour(s) ";

	SetConsoleTextAttribute(hConsole, 10); //set console color font green
	std::cout << min;

	SetConsoleTextAttribute(hConsole, 7); //set console color font white
	std::cout << " min (~";

	SetConsoleTextAttribute(hConsole, 14); //set console color font yellow
	std::cout << min_overall;

	SetConsoleTextAttribute(hConsole, 7); //set console color font white
	std::cout << " mins)" << std::endl;


}

int main(){

	char answer{'y'};
	int count {0};

	do {
		if (count > 0) //check if it's a first run, if not then add a new line. this is just for better output
			std::cout << std::endl;

		int time = EnterValues(0); // check which message to show 0 - for seconds
		int frameAmount = (EnterValues(1)); // // check which message to show 1 - for frames

		PrintResult(time, frameAmount);

		std::cout << std::endl;
		std::cout << "Once again? y/n: ";

		answer = _getch();
		std::cout << std::endl;
		++count;

	} while (answer == 'y');

	return 0;
}