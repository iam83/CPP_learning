#include <iostream>

struct Number{
	int numerator;
	int denominator;
};

using namespace std;

void multiply(Number num1, Number num2){
	cout << "Result: " << static_cast<float>(num1.numerator * num2.numerator) / (num1.denominator * num2.denominator);
}

int main(){

	Number num1;
	Number num2;

	cout << "Enter first numerator: ";
	cin >> num1.numerator;
	cout << "Enter first denominator: ";
	cin >> num1.denominator;
	
	cout << endl;

	cout << "Enter second numerator: ";
	cin >> num2.numerator;
	cout << "Enter second denominator: ";
	cin >> num2.denominator;

	cout << endl;

	multiply(num1, num2);

	return 0;
}