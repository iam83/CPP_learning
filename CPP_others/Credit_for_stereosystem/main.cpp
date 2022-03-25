/*
 
    you get a credit $1000 with 18% interest per year (1.5% per month)
    you have to pay $50 every month from which 1.5% goes to pay debt and the rest is distracted from overall debt

    first month $1000 - 1.5% = $15 goes to debt and $35 pulling from debt $965
    second month $965 - 1.5% = 14.47, $35.52 pulling from debt

*/
#include <iostream>
#include <iomanip> // в заголовочном файле <iomanip> содержится прототип функции setprecision()


int main(){

    int totalMonth = 1;
    float interest = 18;
    float debt = 1000.0;
    float currentDebt = 0;
    float monthPay = 50.0;

    while (debt > 0){

        debt = debt - (monthPay - ((debt*1.5)/100));
        //std::cout << std::setprecision(2) << debt << std::endl;
        std::cout << "Month " << totalMonth << " ";
        std::cout.setf(std::ios::fixed);
        std::cout.setf(std::ios::showpoint);
        std::cout.precision(2);
        std::cout << " debt $" << debt << std::endl;
        if (debt <= 50)
            break;
        totalMonth++;
    }

    std::cout << std::endl;
    std::cout << "Total months: " << totalMonth << std::endl << std::endl;

    return 0;

}
