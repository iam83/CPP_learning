/*
	Выведите на экран следующий массив с помощью цикла:
	 int array[] = { 7, 5, 6, 4, 9, 8, 2, 1, 3 };
*/

#include <iostream>
#include <string>


void PrintArray(int arr[], std::string op, int length){

	int result {};

	//const int length = sizeof(arr) / sizeof(arr[0]); //returns size of pointer instead of array[]

	if (op == "sum"){
		for (int i=0; i < length; ++i){
			result += arr[i];
		}
		std::cout << "Sum of Array = " << result << std::endl;

	}
	if (op == "print"){
		for (int i=0; i < length; ++i){
		std::cout << "Array[" << i << "] = " << arr[i] << std::endl;
		}
	}

}

int main(){

	int array[] = { 7, 5, 6, 4, 9, 8, 2, 1, 3 };
	int length = sizeof(array) / sizeof(array[0]);

	std::string op;

	do {

		std::cout << "Enter 'sum' or 'print': ";
		std::cin >> op;

		if (op == "sum" || op == "print"){
			break;
		}else{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
    		std::cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера;
    		continue;
		}

	} while (1);

	PrintArray(array, op, length);

	return 0;
}