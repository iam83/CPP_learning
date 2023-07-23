#include <iostream>
#include <iomanip>
#include "check.h"
#include "enum.h"
#include <iomanip>

void clearScreen(){

    #ifdef _WIN32
        system("cls");
    #endif
    #ifdef __APPLE__
        system("clear");
    #endif 

}

void printResult(double overall_income, double month_income, int count){
    std::cout << std::showbase << "Month " << std::right << std::setw(2) << count+1 << ": " << std::put_money(overall_income * 100)
            << " per month: " << std::put_money(month_income * 100) << "\n";
}

int main(){

    clearScreen();

    double overall_income{0.0};
    double const interest = 14.5;
    double month_income{0.0};
    // double start_amount = EnterValues("Enter your deposit:> ");
    // double month_amount = EnterValues("How many month(s)?> ");

    double start_amount = 5000000.0;
    double month_amount = 12.0;

    std::cout << std::fixed << std::setprecision(2);
    std::cout.imbue(std::locale("ru_RU.UTF-8"));
    std::cout << std::showbase << "Start amount: " << std::put_money(start_amount * 100) << "\n";
    std::cout << "Interest rate: " << interest << "%\n\n";

    for (int i = 0; i < month_amount; ++i){

        //for the first month
        if (i == 0){
            month_income = (start_amount * (interest / 12.0)) / 100.0;
            overall_income = month_income + start_amount;
            printResult(overall_income, month_income, i);
            continue;
        }

        //calculate for the rest of months
        month_income += ((month_income * (interest / 12.0))) / 100.0;
        overall_income += month_income;
        printResult(overall_income, month_income, i);
        
    }

    #ifdef _WIN32
    std::cout << "\nYour overall income for " << month_amount
              << " month(s) is: " << overall_income;

    std::cout << "\nYour income for " << month_amount
              << " month(s) is: " << overall_income - sum_start;
    #endif

    #ifdef __APPLE__
    std::cout << "\nYour overall income for " << month_amount
              << " month(s) is: " << overall_income;

    std::cout << "\nYour income for " << month_amount
              << " month(s) is: " << "\033[32m" << overall_income - start_amount << "\033[0m\n";
    std::cout << "\n\n";
    #endif

    return 0;

}