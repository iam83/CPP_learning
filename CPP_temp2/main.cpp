/*

    DEBUGGER TESTS

*/

#include <iostream>
#include <memory>
#include <windows.h>

int nScreenWidth = 120;			// Console Screen Size X (columns)
int nScreenHeight = 30;			// Console Screen Size Y (rows)

int main(){

    int a = 8; // create on STACK
    //int b = 7;

    //int *p = new int(10); //create on HEAP

    
    auto p = std::make_unique<int>(a + 2);

    std::cout << "hello\n";


    // Create Screen Buffer
	wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];

	for (int i = 0; i < nScreenWidth*nScreenHeight; i++) screen[i] = L' ';

	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;



    return 0;
}