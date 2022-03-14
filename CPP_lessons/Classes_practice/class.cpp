#include <iostream>
#include <string>


using namespace std;
using namespace std;

//creating base class
class Vehicle {

protected:
	//class fields
	string type;

public:

	//class constructor
	Vehicle(string _type) {
		type = _type;
	}

};


//creating derived class based on Vehicle
class Car : public Vehicle {

private:

	string carName;
	string carColor;
	double maxSpeed;

public:
	//class constructor
	Car(string type, string _carName, string _carColor)
		: Vehicle(type)//using base class to construct base class members
	{
		carName = _carName;
		carColor = _carColor;
		maxSpeed = 0;
	}

	//setter
	void SetCarMaxSpeed(double _maxSpeed) {
		maxSpeed = _maxSpeed;
	}
	void SetColor(string _color) {
		carColor = _color;
	}

	//method
	void GetInfo() {

		cout << "Vehicle type: " << type << endl;
		cout << "Vehicle name: " << carName << endl;
		cout << "Vehicle color: " << carColor << endl;
		cout << "Max speed: " << maxSpeed << " km/h" << endl;
		cout << endl;
	}
};

int main() {

	system("cls");

	Car audi("Car", "Audi", "Red");
	Car bmw("Car", "Bmw", "Green");


	audi.GetInfo();
	bmw.GetInfo();

	audi.SetCarMaxSpeed(250);
	bmw.SetCarMaxSpeed(320);

	audi.SetColor("Blue");

	audi.GetInfo();
	bmw.GetInfo();


	return 0;
}