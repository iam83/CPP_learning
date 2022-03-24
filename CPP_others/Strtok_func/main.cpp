#include <iostream>
#include <cstring>
#include <string>

int main(){


    char str[] = "This is a string - that is going to be parted.";
    
    std::cout << "Parsing string:      " << str << "     for words:\n";

    char * pch = strtok (str," ,.-"); // во втором параметре указаны разделитель (пробел, запятая, точка, тире)
    
    while (pch != NULL){                         // пока есть лексемы
            std::cout << pch  << "\n";
            pch = strtok (NULL, " ,.-");
    }

    system("pause");

    return EXIT_SUCCESS;
}