#include <iostream>
#include <sys/stat.h> // включаем библиотеку sys/stat.h
using namespace std;


string get_creation_date(const string& file_path) {
    struct stat buffer;
    if (stat(file_path.c_str(), &buffer) == 0) { // проверяем, что файл существует
        time_t creation_time = buffer.st_ctime; // сохраняем дату создания в переменную creation_time
        char date_string[20]; // размер строки для хранения даты в виде строки

        struct tm *localtime;
        localtime_r(&creation_time, &localtime); // конвертируем время из time_t в.struct tm*

        strftime(date_string, 20, "%Y-%m-%d %H:%M:%S", localtime); // преобразуем время в строку

        return string(date_string);
    } else {
        return "Файл не найден.";
    }
}

int main() {
    string file_path = "/путь/к/файлу.txt"; // замените на нужный вам путь к файлу
    cout << get_creation_date(file_path) << endl; // выводим дату создания файла

    return 0;
}