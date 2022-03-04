/*
	Определите перечисление (или класс enum) Animal, которое содержит следующих животных:
	pig, chicken, goat, cat, dog и ostrich.

	Напишите функцию getAnimalName(), которая принимает параметр Animal и использует switch для возврата типа животного в качестве строки.

	Напишите еще одну функцию — printNumberOfLegs(), которая использует switch для вывода количества лап соответствующего типа животного.
	Убедитесь, что обе функции имеют кейс default, который выводит сообщение об ошибке. Вызовите printNumberOfLegs() в main(),
    используя в качестве параметров cat и chicken.

    Пример результата выполнения вашей программы:

	A cat has 4 legs.
	A chicken has 2 legs.
*/

#include <iostream>
#include <string>

enum class Animal{
	PIG,
	CHICKEN,
	GOAT,
	CAT,
	DOG,
	OSTRICH,
};

std::string getAnimalName(Animal animal_name){
	switch (animal_name){
		case Animal::PIG:
			return "pig";
			break;
		case Animal::CHICKEN:
			return "chicken";
			break;
		case Animal::GOAT:
			return "goat";
			break;
		case Animal::CAT:
			return "cat";
			break;
		case Animal::DOG:
			return "dog";
			break;
		case Animal::OSTRICH:
			return "ostrich";
			break;
		default:
			return "unknown name";
		}
	}

void printNumberOfLegs(Animal animal){

	std::cout << "A " << getAnimalName(animal) << " has ";

	switch (animal)
    {
        case Animal::CHICKEN:
        case Animal::OSTRICH:
            std::cout << "2";
            break;
 
        case Animal::PIG:
        case Animal::GOAT:
        case Animal::CAT:
        case Animal::DOG:
            std::cout << "4";
            break;
 
        default:
            std::cout << "printNumberOfLegs(): Unhandled enumerator";
            break;
    }
 
    	std::cout << " legs.\n";
}


int main(){

	//std::cout << "Enter animal name: ";
	//string animal_name;
	//std::cin animal_name;

	printNumberOfLegs(Animal::CAT);

	return 0;
}