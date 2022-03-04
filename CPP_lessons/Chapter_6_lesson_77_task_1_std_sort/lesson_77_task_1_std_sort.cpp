#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

int main(){

	//system("clear"); for mac os
	system("cls"); //clear console windows version

	//const int length(9);
	int array[] = { 7, 5, 6, 4, 9, 8, 2, 1, 3, 23, 11, 15, 45, 57 , 90, 100, 95 };

	int length = sizeof(array) / sizeof(array[0]);

	uint16_t startTime = clock();

	sort(array, array+length);


	for (int i = 0; i < length; ++i){
		cout << array[i] << " ";
	}

	uint16_t sortingTime = clock() - startTime;

	cout << "\n\n\n\nSorting completed!\n" <<
        "Sorting time: " << sortingTime << " ms.\n";

	return 0;


}