#include <iostream>


int main(){

    double sum_start{100000.0};
    double overall_income{0.0};
    double const interest = 10.0;
    int month_amount{24};
    double month_income{0.0};

    
       
    
    for (int i = 0; i < month_amount; ++i){

        if (i == 0){
            month_income = (sum_start * (interest / 12)) / 100;
            overall_income = month_income + sum_start;
            std::cout << "Month " << i+1 << ": " << overall_income << " per month: " << month_income << std::endl;
            continue;
        }

        month_income += ((month_income * (interest / 12))) / 100;
        overall_income += month_income;

        std::cout << "Month " << i+1 << ": " << overall_income << " per month: " << month_income << std::endl;
        
    }

    std::cout << "\nYour income for " << month_amount << " month(s) is: "
              << overall_income - sum_start << "\n\n";
    return 0;

}