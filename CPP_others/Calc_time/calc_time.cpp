#include <iostream>
#include <iomanip>
#include <windows.h> //for changing color in console
#include <conio.h> //for getch() function. used for reading key pressing
#include "check.h" //my header file. splitted for learning purpose. used for checking inputs.


void PrintResult(int time, int frameAmount){

	double min_overall = (time*frameAmount)/60.0f;
	int hour = min_overall/60;
	int min = ((time*frameAmount)/60) % 60;

	HANDLE  hConsole;
  	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << std::fixed << std::showpoint;
	std::cout << std::setprecision(1); //set 

	std::cout << std::endl;
	SetConsoleTextAttribute(hConsole, 13); //set console color purple
	std::cout << "Approximate render time is: ";

	SetConsoleTextAttribute(hConsole, 10); //set console color font green
	std::cout << std::abs(hour);

	SetConsoleTextAttribute(hConsole, 7); //set console color font white
	std::cout << " hour ";

	SetConsoleTextAttribute(hConsole, 10); //set console color font green
	std::cout << min;

	SetConsoleTextAttribute(hConsole, 7); //set console color font white
	std::cout << " min (";

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

		double time = EnterValues(0);
		int frameAmount = static_cast<int>(EnterValues(1));

		PrintResult(time, frameAmount);

		std::cout << "Once again? y/n: ";

		answer = getch();
		std::cout << std::endl;
		++count;

	} while (answer == 'y');

	return 0;
}