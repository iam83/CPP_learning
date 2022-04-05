//this program calculates factorial of n using recursive method

#include <iostream>


using namespace std;


double EnterValues(){
	//проверерям корректность ввода, если будут не DOUBLE, то ввод не состоится

	double fact = 0;
	do {

		cout << "Enter number: ";
		cin >> fact;

		if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
        {
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера
            std::cout << "Only numbers please\n" << endl;
        }
        else
        {
            std::cin.ignore(32767,'\n'); // удаляем лишние значения
 			break;
        }
	} while(1);

	return fact;
}


//calcualte factorial using recursive function
//using <double> bc int is too small to keep values 
double CalcFactorialRecursive(double n){

	if (n == 1){
		return n;
	}
	return n * CalcFactorialRecursive(n-1);

}

//calculate factorial of n using for-loop
double CalcFactorial(double n){

	double result = 1;

	for (int i=1; i<=n; ++i){
		result *= i;
	}
	return result;
}

int main(){

	system ("clear"); //clear MacOS terminal
	int fact = EnterValues();
	cout << "Factorial of " << fact << " = " << CalcFactorialRecursive(fact) << endl;
	return 0;
}