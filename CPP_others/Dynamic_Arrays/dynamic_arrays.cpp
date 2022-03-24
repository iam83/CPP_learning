/*
    creating and bubble sorting dynamic arrays
*/


#include <iostream>
#include <algorithm>
#include <ctime>   // в заголовочном файле <ctime> содержится прототип функции time()
#include <iomanip> // в заголовочном файле <iomanip> содержится прототип функции setprecision()


void printArray(float* pArray, int amount) //передаем указатель на массив
    {
        for (int count = 0; count < amount; count++)
            std::cout << std::setprecision(2) << pArray[count] << " ";
        std::cout << std::endl;
    }

int main(){

    system("clear");

    srand(time(0)); // генерация случайных чисел
    int amount(5); // количество ячеек

    float *pArray = new float [amount]; // создание динамического массива вещественных чисел на десять элементов
    
    for (int count = 0; count < amount; count++)
        //заполнение массива случайными числами с масштабированием от 1 до 10
        pArray[count] = (rand() % 10 + 1) / float((rand() % 10 + 1));
    
    std::cout << "array = ";

    printArray(pArray, amount);
    std::cout << std::endl;
    
    int iteration(0);
    while(iteration < amount){

        bool swapped = false;
        std::cout << "iteration " << iteration + 1;

        for (int j = 0; j < amount - 1 - iteration; ++j)
        {
            if (pArray[j] > pArray[j+1]){
                //std::cout << pArray[j] << "   " << pArray[j+1] << '\n';
                //std::swap(pArray[j], pArray[j+1]);
                swapped = true;
            }
        }

        if (!swapped){
            std::cout << std::endl;
            std::cout << "Early termination on iteration " << iteration + 1 << "\n";
            break;
        }

        std::cout << std::endl;
        printArray(pArray, amount);
        std::cout << std::endl;

        ++iteration;
    }

    std::cout << "sorted = ";

    printArray(pArray, amount);

    delete [] pArray;            // высвобождение памяти
    //system("pause");             // windows console pause

    return 0;
}