#include <iostream>

//with IF
int sumTo(int x){

	int res {0};

	for (int count = 1; count <= x; ++count){
		if (count != x){
			std::cout << count << " + ";
		}else{
			std::cout << count;
		}
		res += count;
	}
	std::cout << " = ";
	return res;
}

int main(){

	std::cout << sumTo(5) << std::endl << std::endl;
	return 0;
}