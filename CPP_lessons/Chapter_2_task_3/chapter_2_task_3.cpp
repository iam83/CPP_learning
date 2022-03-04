#include <iostream>


using namespace std;

double getUserInput(){

	cout << "Enter a double value: ";
	double value;
	cin >> value;
	return value;
}

char getOp(){

	cout << "Enter one of the following: +, -, *, or /: ";
	char op;
	cin >> op;
	return op;
}

void getResult(double first_value, double second_value, char op){

	if (op != '+' && op != '-' && op != '*' && op != '/'){
		cout << "Enter correct sign" << endl;
	}

	if (op == '+')
		cout << first_value << " + " << second_value << " = " << first_value + second_value;
	else if (op == '-')
		cout << first_value << " - " << second_value << " = " <<first_value - second_value;
	else if (op == '*')
		cout << first_value << " * " << second_value << " = " <<first_value * second_value;
	else if (op == '/')
		cout << first_value << " / " << second_value << " = " << first_value / second_value;

}

int main(){

	getResult(getUserInput(), getUserInput(), getOp());
	return 0;

}