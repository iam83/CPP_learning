#include <iostream>

int add(int x, int y);

int main(){

    FILE *pFile = fopen("sum.txt", "w"); //C style

    std::cout << add(5,5) << std::endl;

    fprintf(pFile, "sum\n"); 
    fclose(pFile);
    
    system("pause");
    return 0;
} 