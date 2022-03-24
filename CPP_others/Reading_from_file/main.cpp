//пример использования FILE
 
#include <cstdio>

int main()
{
   char buffer[100];
 
   FILE * ptrFile = fopen("file.txt" , "r");
 
   if (ptrFile == NULL) perror ("Error");
   else
   {
     while ( !feof(ptrFile) )                               // пока не конец файла
     {
       if ( fgets(buffer , 100 , ptrFile) != NULL )         // считать символы из файла
         fputs(buffer, stdout);                           // вывод на экран
     }
 
     fclose (ptrFile);                                      // закрыть файл
   }
   return 0;
}