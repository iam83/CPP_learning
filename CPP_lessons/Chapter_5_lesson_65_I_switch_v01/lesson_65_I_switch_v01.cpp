/*
 Напишите функцию calculate(), которая принимает две переменные типа int и одну переменную типа char
 которая, в свою очередь, представляет одну из следующих математических операций: +, -, *, / или % (остаток от числа).
 Используйте switch для выполнения соответствующей математической операции над целыми числами,
 а результат возвращайте обратно в main(). Если в функцию передается недействительный математический оператор,
 то функция должна выводить ошибку. С оператором деления выполняйте целочисленное деление.
 */

#include <iostream>

int calculate(int x, int y, char c){

	switch (c){
		case '+':
			return x + y;
			break;
		case '-':
			return x - y;
			break;
		case '/':
			return x / y;
			break;
		case '*':
			return x * y;
			break;
		case '%':
			return x % y;
			break;
		default:
			std::cout << "calculate(): Unhandled case" << std::endl;
			return 0; 
	}
}

int main(){

	system("clear");

	std::cout << "Enter x: ";
	int x;
	std::cin >> x;
	std::cin.ignore(32767, '\n');

	std::cout << "Enter y: ";
	int y;
	std::cin >> y;
	std::cin.ignore(32767, '\n');

	std::cout << "Enter sign of operation (+, -, /, *, %): ";
	char c;
	std::cin >> c;
	
	std::cin.ignore(32767, '\n');
	std::cout << std::endl;

	std::cout << "Result: " << calculate(x, y, c);

	return 0;
}