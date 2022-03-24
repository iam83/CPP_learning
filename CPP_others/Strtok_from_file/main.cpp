// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

int main () {
    
    system("cls");

    std::string line;
    std::ifstream myfile ("text.txt");

    char *c_str = new char [line.length()+1];

    if (myfile.is_open())
  {
    while (getline(myfile,line))
    {
      std::cout << line << '\n';
      //std::strcpy (c_str, line.c_str());
    }

    myfile.close();

    }else{
      std::cout << "Unable to open file"; 
    }

    char * pch = strtok(c_str," ,.-"); // во втором параметре указаны разделитель (пробел, запятая, точка, тире)
    
    while (pch != NULL){                         // пока есть лексемы
            std::cout << pch  << "\n";
            pch = strtok (NULL, " ,.-");
    }

    delete[] c_str;

    system("pause");



  return 0;
}
