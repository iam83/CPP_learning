#include <iostream>

using namespace std;

int getNumber(){

	cout << "Enter integer number (0-255): ";
	int x;
	cin >> x;
	if (x > 255 || x < 0)
	{
		cout << "Incorrect number" << endl;
		return 0;
	}
	else
	{
		return x;
	}
}

void printNumber(int num){

	if (num >= 128){
		cout << 1;
		num -= 128;
	}
	else{
		cout << 0;
	}

	if (num >= 64){
		cout << 1;
		num -= 64;
	}
	else{
		cout << 0;
	}
	if (num >= 32){
		cout << 1;
		num -= 32;
	}
	else{
		cout << 0;
	}

	if (num >= 16){
		cout << 1;
		num -= 16;
	}
	else{
		cout << 0;
	}
	cout << " ";
	if (num >= 8){
		cout << 1;
		num -= 8;
	}
	else{
		cout << 0;
	}
	if (num >= 4){
		cout << 1;
		num -= 4;
	}
	else{
		cout << 0;
	}

	if (num >= 2){
		cout << 1;
		num -= 2;
	}
	else{
		cout << 0;
	}

	if (num == 1){
		cout << 1;
	}
	else{
		cout << 0;
	}


}

int main(){

	printNumber(getNumber());
	return 0;

}