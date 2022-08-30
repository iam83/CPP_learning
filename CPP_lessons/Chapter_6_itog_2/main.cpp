/*

        Создайте структуру, содержащую имя и оценку учащегося (по шкале от 0 до 100).
        Спросите у пользователя, сколько учеников он хочет ввести.
        Динамически выделите массив для хранения всех студентов.
        Затем попросите пользователя ввести для каждого студента его имя и оценку.
        Как только пользователь ввел все имена и оценки, отсортируйте список оценок студентов
        по убыванию (сначала самый высокий бал).
        Затем выведите все имена и оценки в отсортированном виде.

        Для следующего ввода:
        Andre
        74
        Max
        85
        Anton
        12 
        Josh
        17
        Sasha
        90

        Вывод должен быть следующим:
        Sasha got a grade of 90
        Max got a grade of 85
        Andre got a grade of 74
        Josh got a grade of 17
        Anton got a grade of 12
        
        Подсказка: Вы можете изменить алгоритм сортировки массива методом выбора из урока No80
        для сортировки вашего динамического массива.
        Если вы напишете сортировку массива отдельной функцией,
        то массив должен передаваться по адресу (как указатель).

*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>


struct Student{
    std::string name;
    int grade;
};

bool reverse(Student &a, Student &b){
    return (a.grade > b.grade);
}

int main(){

    bool write{true}; //enable or disable to write to text file

    std::cout << std::endl;
    std::cout << "How many students would you like to enter: ";

    std::vector<Student> studentArray;

    int studentAmount{0};
    std::cin >> studentAmount;

    if (studentAmount == 0)
        return 0;

    for (int i = 0; i < studentAmount; ++i){

        std::cout << "Enter student #" << i + 1 << std::endl;
        Student student;
        std::cin >> student.name >> student.grade;
        studentArray.push_back(student);

    }

    //sorting studentArray
    std::sort(studentArray.begin(), studentArray.end(), reverse);

    std::ofstream file ("output.txt");

    for (int i = 0; i < studentArray.size(); ++i){
        std::cout << studentArray[i].name << " got a grade of " << studentArray[i].grade << std::endl;
        
        //writing to file
        if(file.is_open() && write){
            file << studentArray[i].name << " got a grade of " << studentArray[i].grade << std::endl;
        }
    }

    file.close();

    return 0;
}