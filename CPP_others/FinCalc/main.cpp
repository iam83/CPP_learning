#include <iostream>
#include <iomanip>
#include "check.h"
#include "enum.h"

#ifdef _WIN32
	#include <windows.h> //for changing color in console
	#include <conio.h> //for getch() function. used for reading key pressing
#endif

void printResult(double value, int count, std::string message, bool isSpaceAtTheEnd){

    // HANDLE  hConsole;
    // hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // SetConsoleTextAttribute(hConsole, consoleColor);

    std::cout << std::fixed << std::setprecision(2);
    if (isSpaceAtTheEnd)
        std::cout << message << value;
    else
        std::cout << message << count+1 << ": " << value;
    if (isSpaceAtTheEnd) std::cout << "\n";

    //SetConsoleTextAttribute(hConsole, ConsoleColor::NormalWhite);
}

int main(){

    double overall_income{0.0};
    double const interest = 10.0;
    double month_income{0.0};
    double sum_start = EnterValues("Enter your deposit:> ");
    double month_amount = EnterValues("How many month(s)?> ");

    for (int i = 0; i < month_amount; ++i){

        if (i == 0){

            printResult(sum_start, i, "Month: ", false);
            month_income = (sum_start * (interest / 12.0)) / 100.0;
            overall_income = month_income + sum_start;
            printResult(month_income, i, " per month: ", true);
            continue;
        }

        printResult(overall_income, i, "Month: ", false);

        month_income += ((month_income * (interest / 12.0))) / 100.0;
        overall_income += month_income;

        printResult(month_income, i, " per month: ", true);

        
    }

    
    printResult(month_amount, 0, "\nYour overall income for ", false);
    printResult(overall_income, 0, " month(s) is: ", false);

    printResult(month_amount, 0, "\nYour income for ", false);
    printResult(overall_income - sum_start, 0, " month(s) is: ", false);

    std::cout << "\n\n";

    return 0;

}