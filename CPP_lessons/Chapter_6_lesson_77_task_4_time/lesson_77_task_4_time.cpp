////////////////////////////////////////////////////////////////////////////
// https://ravesli.com/urok-77-sortirovka-massivov-metodom-vybora/#toc-3
// сортировка массима с замером времени
//////////

#include <iostream>
#include <random>
#include <ctime>
#include <utility>
 
int randomNumberGenerator()
{
    std::random_device rand;
    std::mt19937 mersenneTwister(rand());
    int mtGenerated = mersenneTwister() % 1000 + 1;
 
    return mtGenerated;
}
 
int main()
{
    const int length{ 1000 };
    int array[length];
 
    //заполняем массив
    for (int index = 0; index < length; ++index)
        array[index] = randomNumberGenerator();
 
    std::cout << "GENERATED ARRAY: \n";
    for (int i = 0; i < length; ++i)
    {
        std::cout << array[i] << " ";
    }
 
    //статистика
    std::uint32_t amountOfSwaps{ 0 };
    int iteration{ 0 };
    std::uint16_t startTime = clock();
 
    //начало сортировки
    for (iteration; iteration < (length - 1); ++iteration)
    {
        int dynamicLength{ length - iteration };
        bool isSwapped{ false };
 
        for (int currentIndex = 0; currentIndex < (dynamicLength - 1); ++currentIndex)
        {
            if (array[currentIndex] > array[currentIndex + 1])
            {
                std::swap(array[currentIndex], array[currentIndex + 1]);
                    isSwapped = true;
                    ++amountOfSwaps;
            }
        }
 
        if (!isSwapped) break;
    }
    //засекаем время выполнения 
    std::uint16_t sortingTime = clock() - startTime;
 
    for (int i = 0; i < 10; ++i)
        std::cout << "\n";
 
    std::cout << "SORTED ARRAY: \n";
    for (int i = 0; i < length; ++i)
        std::cout << array[i] << " ";
 
    std::cout << "\n\n\n\nSorting completed!\n" <<
        " Iterations: " << ++iteration << "\n" <<
        " Swaps: " << amountOfSwaps << "\n" <<
        " Sorting time: " << sortingTime << " ms.\n\n\n\n";
 
    std::cin.get();
    return 0;
}