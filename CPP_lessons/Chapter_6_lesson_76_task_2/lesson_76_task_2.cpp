/*

Попросите пользователя ввести число от 1 до 9. Если пользователь введет что-либо другое
— попросите его снова ввести число и так до тех пор, пока он не введет корректное значение из заданного диапазона.
Как только пользователь введет число от 1 до 9, выведите массив на экран.
Затем найдите в массиве элемент с числом, которое ввел пользователь, и выведите его индекс.

*/

#include <iostream>
#include <string>

int main(){

	int array[] = { 7, 5, 6, 4, 9, 8, 2, 1, 3 };
	int array_length = sizeof(array) / sizeof(array[0]);

	int number{0};

	do{

		std::cout << "Enter a number between 1-9: ";
		std::cin >> number;

		// Если пользователь ввел некорректное значение 
        if (std::cin.fail())
            std::cin.clear(); 
 
        std::cin.ignore(32767, '\n');


    }while(number < 1 || number > 10); //eg. number=12, while(12 < 1 'false' || 12 > 10 'true') == true

	for (int i = 0; i < array_length; ++i){
		std::cout << array[i] << " ";
	}

	std::cout << "\n";

	for (int i = 0; i < array_length; ++i){

		if (array[i] == number){
			std::cout << "Index of " << number << " = " << i << std::endl;
		}
	}

}