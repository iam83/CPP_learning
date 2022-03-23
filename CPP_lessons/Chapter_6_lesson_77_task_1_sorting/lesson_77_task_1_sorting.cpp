///////////////////////////////////////////////////////////////////////
//
//	 Напишите программу, которая отсортирует следующий массив сортировкой пузырьком в соответствии с правилами,
//	 указанными выше: https://ravesli.com/urok-77-sortirovka-massivov-metodom-vybora/
//
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

int main(){

	system("clear");

	//const int length(9);
	int array[] = { 7, 5, 6, 4, 9, 8, 2, 1, 3, 23, 11, 15, 45, 57 , 90, 100, 95 };

	int length = sizeof(array) / sizeof(array[0]);

	uint16_t startTime = clock();

	for (int iteration = 0; iteration < length - 1; ++iteration){

		bool swapped(false); // отслеживаем, были ли выполнены замены в этой итерации

		// Перебираем каждый элемент массива до последнего элемента (не включительно).
        // Последний элемент не имеет пары для сравнения

		for (int currentIndex = 0; currentIndex < length - 1 - iteration; ++currentIndex){

			if (array[currentIndex] > array[currentIndex + 1]){
				swap(array[currentIndex], array[currentIndex + 1]);
				swapped = true;
			}

			cout << array[currentIndex] << " ";
		}

		cout << endl;

		// Если в этой итерации не выполнилось ни одной замены, то цикл можно завершать
        if (!swapped)
        {
            // Выполнение начинается с 0-й итерации, но мы привыкли считать, начиная с 1,
            // поэтому для подсчета количества итераций добавляем единицу
            cout << "Early termination on iteration: " << iteration + 1 << '\n';
            break;
        }


	}

	for (int i = 0; i < length; ++i){
		cout << array[i] << " ";
	}

	uint16_t sortingTime = clock() - startTime;

	cout << "\n\n\n\nSorting completed!\n" <<
        "Sorting time: " << sortingTime << " ms.\n";

	return 0;
}