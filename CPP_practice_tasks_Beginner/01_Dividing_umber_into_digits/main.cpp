//Составить программу, которая будет считывать введённое пятизначное число.
// После чего, каждую цифру этого числа необходимо вывести в новой строке.
/*

					Деление числа на разряды

				Введите пятизначное число: 10819

				1 цифра равна 1
				2 цифра равна 0
				3 цифра равна 8
				4 цифра равна 1
				5 цифра равна 9

*/

#include <iostream>

int getInput() {

	int number;

	do {
		std::cin >> number;

		if (std::cin.fail()) // // если предыдущее извлечение оказалось неудачным,
		{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
			std::cout << "Only numbers please" << std::endl;
		}
		else
		{
			std::cin.ignore(32767, '\n'); // удаляем лишние значения

			if (number < 1 || number > 99999) {
				std::cout << "Enter number between 1 - 9999" << std::endl;
				continue;
			}
			else {
				break;
			}
		}
	} while (1);

	return number;
}

int main() {

	std::cout << "Enter a number between 1 - 99999: " << std::endl;

	int number = getInput();
	std::cout << "You entered " << number << std::endl;

	std::cout << "1 digit is " << (number/10000) << std::endl;
	std::cout << "2 digit is " << (number/1000) % 10 << std::endl;
	std::cout << "3 digit is " << (number/100) % 10 << std::endl;
	std::cout << "4 digit is " << (number/10) % 10<< std::endl;
	std::cout << "5 digit is " << number % 10 << std::endl;

	return 0;
}