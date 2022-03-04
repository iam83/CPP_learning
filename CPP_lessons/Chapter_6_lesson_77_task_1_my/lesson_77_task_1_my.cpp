///////////////////////////////////////////////////////////////////////
//
//	 Напишите программу, которая отсортирует следующий массив сортировкой пузырьком в соответствии с правилами, указанными выше:
//		https://ravesli.com/urok-77-sortirovka-massivov-metodom-vybora/
//   MY SOLUTION (working but not optimized)
//
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

int main(){

	system("clear");

	const int length(17);
	int array[length] = { 7, 5, 6, 4, 9, 8, 2, 1, 3, 23, 11, 15, 45, 57 , 90, 100, 95 };
	int index = 0;

	uint16_t startTime = clock();

	while (index < length){

		bool swapped (false);

		for (int currentIndex = 0; currentIndex < length; ++currentIndex){

			if (array[currentIndex] > array[index]){
				swap(array[currentIndex], array[index]);
				swapped = true;
			}

			cout << array[currentIndex] << " ";
		}
		++index;

		if (!swapped)
        {
            // Выполнение начинается с 0-й итерации, но мы привыкли считать, начиная с 1, поэтому для подсчета количества итераций добавляем единицу
            cout << "Early termination on iteration: " << index + 1 << '\n';
            break;
        }

		cout << endl;
	}

	uint16_t sortingTime = clock() - startTime;

	for (int i = 0; i < length; ++i){
		cout << array[i] << " ";
	}

	cout << "\n\n\n\nSorting completed!\n" <<
        "Sorting time: " << sortingTime << " ms.\n";

	return 0;
}