/*Напишите программу, которая просит у пользователя ввести его имя, фамилию и возраст.
В результате, укажите пользователю, сколько лет он прожил на каждую букву из его имени и фамилии
(чтобы было проще, учитывайте также пробелы). Например:

Enter your full name: Tom Cats
Enter your age: 45
You've lived 5.625 years for each letter in your name.

Уточнение: Возраст 45 делится на длину имени и фамилии «Tom Cats» (8 букв, учитывая пробел), что равно 5.625.
*/


#include <iostream>
#include <string>


int main(){

	std::cout << "Enter your full name: ";
	std::string fullName;
	std::getline(std::cin, fullName);

	std::cout << "Enter your age: ";
	int age;
	std::cin >> age;

	std::cout << "You've lived " << static_cast<double>(age)/fullName.length()
			  << " years for each letter in your name" << std::endl;

	return 0;

}