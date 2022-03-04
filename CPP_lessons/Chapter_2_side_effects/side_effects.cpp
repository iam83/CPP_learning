
#include <iostream>
 
int main()
{
	int x = 5;
	int y = x++; // 5 goes to y=5, then x+1 = 6

	std::cout << x << std::endl; //6
	std::cout << y << std::endl; //5

	int z = 5;
	int w = ++z; // z+1=6 goes to y=6

	std::cout << z << std::endl; //6
	std::cout << w << std::endl; //6
}