/*
        Calculate bank deposit
*/

#include <iostream>
#include <iomanip> //for monetary output
#include <string>
#include "check.h" //check if enter is valid
#include "ccolor.h" //terminal color
#include <format>


#ifdef _WIN32
#include <locale>

#define FACTOR 1.0
#endif

#ifdef __APPLE__
#define FACTOR 100.0
#endif


/* creating custom ostream object // usage std::cout << myTest; //output: test

std::ostream& myTest(std::ostream& os) {
    std::string myStr = "test";
    os << myStr;
    return os;
}
*/

void clearScreen(){

    #ifdef _WIN32
        system("cls");
    #endif
    #ifdef __APPLE__
        system("clear");
    #endif

}

void printResult(double overall_income, double month_income, int count){

    std::cout << std::showbase << "Month "
              << std::right << std::setw(2) << count+1 << ":   "
              << setColor(CColor::Green) << std::put_money(overall_income * FACTOR) << setColor(CColor::Reset)
              << "    profit per month:  " << setColor(CColor::Cyan) << std::put_money(month_income * FACTOR) << setColor(CColor::Reset) << "\n";
}

int main(){

    //setlocale(LC_ALL, "Russian");
    setColor(CColor::Reset);

    clearScreen();

    double overall_income {0.0};
    double month_income {0.0};

    // double start_amount = EnterValues("Enter your deposit:> ");
    // double month_amount = EnterValues("How many month(s)?> ");
    // double interest = EnterValues("At what interest %?> ");

    //for test purpose
    double const interest {15.0};
    double start_amount {1'000'000.0};
    double month_amount {12.0};


    std::cout << std::fixed << std::setprecision(2);

    #ifdef __APPLE__
    std::cout.imbue(std::locale("ru_RU.UTF-8"));
    #endif
    std::cout << setColor(CColor::BG_Yellow);
    std::cout << std::showbase << "\nStart amount: " << std::put_money(start_amount * FACTOR) << "\n";
    std::cout << setColor(CColor::Reset);
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


    std::cout << "\nYour overall income for "
              << setColor(CColor::Cyan) << static_cast<int>(month_amount)
              << setColor(CColor::Reset) << " month(s) at "
              << setColor(CColor::Magenta) << interest << "%"
              << setColor(CColor::Reset) << " is: "
              << setColor(CColor::Green) << std::put_money(overall_income * FACTOR)
              << setColor(CColor::Reset);

    std::cout << "\nYour income for "
              << setColor(CColor::Cyan) << static_cast<int>(month_amount)
              << setColor(CColor::Reset) << " month(s) is: "
              << setColor(CColor::Green) << std::put_money((overall_income - start_amount) * FACTOR)
              << setColor(CColor::Reset);
    std::cout << "\n\n";

    //system("pause");
    return 0;

}