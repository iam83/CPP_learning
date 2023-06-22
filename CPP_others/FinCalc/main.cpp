#include <iostream>
#include <iomanip>
#include "check.h"
#include "enum.h"



void printResult(double overall_income, double month_income, int count){
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Month " << count+1 << ": " << overall_income
              << " per month: " << month_income << "\n";
}

int main(){

    double overall_income{0.0};
    double const interest = 10.0;
    double month_income{0.0};
    double sum_start = EnterValues("Enter your deposit:> ");
    double month_amount = EnterValues("How many month(s)?> ");

    std::cout << "Interest rate: " << interest << "%\n\n";

    for (int i = 0; i < month_amount; ++i){

        //for the first month
        if (i == 0){
            month_income = (sum_start * (interest / 12.0)) / 100.0;
            overall_income = month_income + sum_start;
            printResult(sum_start, month_income, i);
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
              << " month(s) is: " << "\033[32m" << overall_income - sum_start << "\032[0m\n";
    std::cout << "\n\n";
    #endif

    return 0;

}