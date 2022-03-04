#include <iostream>

using namespace std;

//check if number is even
bool isEven(int number){
	return (number % 2) == 0;
}

int main(){

	cout << "Enter integer number: ";
	int number;
	cin >> number;

	if (isEven(number))
		cout << number << " is even." << endl;
	else
		cout << number << "is odd." << endl;
	return 0;
}