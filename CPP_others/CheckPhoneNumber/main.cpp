#include <iostream>
#include <string>
#include <fstream>

// +7 123 456 78 90

void printFormatPhoneNumber(std::string &phone){

    phone.erase(0,1);
    std::cout << "Your phone number is: +7 ";
    for (int i = 0; i < phone.length(); i++){
        if (i <= 2)
            std::cout << phone[i];
        if (i == 3)
            std::cout << " ";
        if (i >=3 && i<=5)
            std::cout << phone[i];
        if (i == 6)
            std::cout << " ";
        if (i >=6 && i <= 7)
            std::cout << phone[i];
        if (i == 8)
            std::cout << " ";
        if (i >= 8 && i <= 9)
            std::cout << phone[i];
    }
   
    std::cout << std::endl;
}

void formatPhoneNumber(std::string &phone){
     //inserting spaced into unformatted phone number
    phone.erase(0,1);
    phone.insert(3, " ");
    phone.insert(7, " ");
    phone.insert(10, " ");
    phone.insert(0, "+7 ");
}

int main(){

    std::string phone = " ";

    //entering phone number
    while(1){

        std::cout << "Enter phone number: ";
        std::cin >> phone;

        if (phone.length() == 11){ //if it's correct then break
            break;
        }else{
            std::cout << "Wrong number. Please try again.\n" << std::endl;
        }
    }

    //first attempt
    //printFormatPhoneNumber(phone); 

    //second attempt using string methods
    formatPhoneNumber(phone); //passing argument by reference
    std::cout << "Your phone number is: ";
    std::cout << phone << std::endl;

    std::ofstream file ("phone_number.txt");
    if(file.is_open()){
        file << "Phone number: " << phone << std::endl;
        file.close();
    }

    return 0;
}