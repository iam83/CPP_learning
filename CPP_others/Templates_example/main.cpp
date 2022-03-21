#include <iostream>

using namespace std;

template<typename T>

void Swap(T& a, T& b) {

	T temp = a;
	a = b;
	b = temp;
}


int main() {


	int a, b;

	cout << "Enter a: ";
	cin >> a;
	cout << "Enter b: ";
	cin >> b;

	cout << "a = " << a << " and " << "b = " << b << endl;

	Swap(a, b);

	//Swap<int>(a, b); //alternatively it can be like this to explicilty show the data type


	cout << "After swapping" << endl;
	cout << "a = " << a << " and " << "b = " << b << endl;

	return 0;

}