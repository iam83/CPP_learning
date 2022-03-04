#include <iostream>

using namespace std;

int getNumber(){
	cout << "Enter integer number (0-255): ";
	int x;
	cin >> x;
	if (x > 255 || x < 0)
		return -1;
	else{
		return x;
	}
}

int checkNumber(int num, const int digit){

	if (num >= digit){
		cout << 1;
		num -= digit;
		return num;
	}
	else{
		cout << 0;
		return num;
	}
}

int main(){
	system("cls");
	
	int num = getNumber();
	int x;

	x = checkNumber(num, 128);
	x = checkNumber(x, 64);
	x = checkNumber(x, 32);
	x = checkNumber(x, 16);
	x = checkNumber(x, 8);
	x = checkNumber(x, 4);
	x = checkNumber(x, 2);
	x = checkNumber(x, 1);

	return 0;

}