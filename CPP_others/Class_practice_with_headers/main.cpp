#include <iostream>
#include "car.h"


int main() {


		Car audi ("Audi", "Green", 250.0);
	
		audi.GetInfo();

		audi.SetColor("Red");
		audi.SetSpeed(235.5);
		audi.GetInfo();

		Car bmw("BMW", "Blue", 320.0);

		bmw.GetInfo();
		
		bmw.SetColor("Black");


		bmw.GetInfo();
		audi.GetInfo();

		return 0;

}