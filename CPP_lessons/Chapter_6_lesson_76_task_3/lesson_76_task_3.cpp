/*

    Измените следующую программу так, чтобы вместо maxScore с наибольшим значением,
    переменная maxIndex содержала индекс элемента с наибольшим значением:

*/


#include <iostream>
 
int main()
{
    int scores[] = { 73, 85, 84, 44, 78 };
    const int numStudents = sizeof(scores) / sizeof(scores[0]);
 
    int maxIndex = 0; // отслеживаем самую высокую оценку

    for (int student = 0; student < numStudents; ++student)
        if (scores[student] > scores[maxIndex]){
            maxIndex = student;
        }
    std::cout << "The index of the best score is " << maxIndex << '\n';
 
    return 0;
}
