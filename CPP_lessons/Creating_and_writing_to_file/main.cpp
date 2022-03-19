#include <iostream>

int main(){

    FILE *pfile = fopen("test.txt", "W");
    
    fprintf(pfile, "Hello World");
    fclose(pfile);
    return 0;
} 