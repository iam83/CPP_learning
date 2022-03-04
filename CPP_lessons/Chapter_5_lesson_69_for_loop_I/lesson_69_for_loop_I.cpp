#include <iostream>

//with IF
void print_even_v1(){
	for (int count = 0; count <= 20; ++count){
		if (count % 2 == 0){
			std::cout << count << std::endl;
		}
	}
}

//without IF
void print_even_v2(){
	for (int count = 0; count <= 20; count += 2){
			std::cout << count << std::endl;
	}
}
int main(){

	print_even_v1();
	print_even_v2();

	return 0;
}