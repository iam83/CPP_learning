/*

	Hi-Lo game  https://ravesli.com/glava-5-itogovyj-test/

	Напишите программу-игру типа Hi-Lo:

   Во-первых, ваша программа должна выбрать случайное целое число в диапазоне от 1 до 100.

   Пользователю дается 7 попыток, чтобы угадать это число.

   Если пользователь не угадал число, то программа должна подсказывать,
   была ли его догадка слишком большой или слишком маленькой.

   Если пользователь угадал число, то программа должна сообщить, что всё верно — вы выиграли.

   Если же у пользователя кончились попытки, и он не угадал число,
   то программа должна сообщить ему, что он проиграл и показать правильный результат.

   В конце игры программа должна спросить у пользователя, не хочет ли он сыграть еще раз.
   Если пользователь не введет ни y, ни n (а что-то другое), то программа должна спросить его еще раз.

*/

#include <iostream>
#include <cstdlib> // для функций rand() и srand()
#include <ctime> // для функции time()

using namespace std;

int getRandomNumber()
{
    return rand()%100+1;
}

int playAgain(){

	char exit;

	do{
		cout << "Would you like to play again (y/n)?: ";
		cin >> exit;

        if (exit == 'y'){
			return 1;
			break;
		}else if(exit == 'n'){
			cout << "Thank you for playing." << endl;
			return 0;
			break;
		}else{
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
    		std::cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера
		}


	}while(1);

	cout << endl;
}

int getAnswer(){

	int number;

	do {
		cin >> number;

		if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
        {
            std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
            std::cin.ignore(32767,'\n'); // и удаляем значения предыдущего ввода из входного буфера
            std::cout << "Only numbers please" << endl;
        }
        else
        {
            std::cin.ignore(32767,'\n'); // удаляем лишние значения
 
            	if (number < 1 || number > 100){
					cout << "Enter number between 1 - 100" << endl;
					continue;
				}else{
					break;
				}
        }
	} while(1);

	return number;
}

int main(){

	srand(static_cast<unsigned int>(time(0)));

	do{
			system("clear");			
			cout << "Let's play a game." << endl;
			cout << "I'm thinking of a number between 1-100. You have 7 tries to guess what it is." << endl;

			int guess_number = getRandomNumber(); //получаем рандомное число
		    //cout << guess_number << endl; //для теста	
			int attempts = 1; //количество попыток
			int answer = 0;
			int check = 0;

		while (attempts <= 7){

			cout << "Guess #" << attempts << ": ";

			int answer = getAnswer();

			if (answer > guess_number){
				cout << "Your guess is too high." << endl;
			}else if(answer < guess_number){
				cout << "Your guess is too low." << endl;
			}else{
				cout << endl;
				cout << "Congratulations! You win!" << endl;
				check = 1;
				break;
			}
			check = 0;
			++attempts;
		}

		if (!check){
			cout << endl;
			cout << "Sorry, you lose. The correct number was: " << guess_number << endl;
		}

	} while(playAgain());

	return 0;
}