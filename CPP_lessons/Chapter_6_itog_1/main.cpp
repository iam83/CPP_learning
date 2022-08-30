/*

Представьте, что вы пишете игру,
в которой игрок может иметь 3 типа предметов: зелья здоровья, факелы и стрелы.
Создайте перечисление с этими типами предметов и фиксированный массив
для хранения количества каждого типа предметов, которое имеет
при себе игрок (используйте стандартные фиксированные массивы, а не std::array).
У вашего игрока должны быть при себе 3 зелья здоровья, 6 факелов и 12 стрел.
Напишите функцию countTotalItems(), которая возвращает общее количество предметов,
которые есть у игрока.
В функции main() выведите результат работы функции countTotalItems().

*/

#include <iostream>

enum ItemTypes{

    HEALTH,
    TORCH,
    ARROW,
    MAX_ITEMS

};

int countTotalItems(int *items) // нам здесь не нужно передавать длину массива, так как она уже указана членом MAX_ITEMS перечисления ItemTypes
{
    int totalItems = 0;
    for (int index = 0; index < MAX_ITEMS; ++index)
        totalItems += items[index];
    return totalItems;
}

int main(){

    int items[MAX_ITEMS]{3, 6, 12};
    std::cout << "The player has " << countTotalItems(items) << " items in total.\n";

    return 0;
}