#include <iostream>

int add(int x, int y);

int main(){

    FILE *pFile = fopen("sum.txt", "w");

    std::cout << add(5,5) << std::endl;

    fprintf(pFile, "sum\n"); 
    fclose(pFile);
 
    return 0;
} 