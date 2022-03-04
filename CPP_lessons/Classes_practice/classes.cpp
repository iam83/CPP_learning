#include <iostream>
#include <string>

using namespace std;


class Car {

private:

	string carName;
	string carColor;
	double maxSpeed;

public:

	Car(string car_name, string car_color) {
		carName = car_name;
		carColor = car_color;
		maxSpeed = 0.0f;
	}

	void GetInfo() {
		cout << "Car name: " << carName << endl;
		cout << "Car color: " << carColor << endl;
		cout << "Max speed: " << maxSpeed << endl;
		cout << endl;

	}
	void SetCarMaxSpeed(double max_speed) {
		maxSpeed = max_speed;
	}

};

int main() {

	system("cls");

	Car bmw("BMW", "Red");
	Car audi("Audi", "Green");
	bmw.GetInfo();
	audi.GetInfo();

	bmw.SetCarMaxSpeed(250);
	bmw.GetInfo();

	audi.SetCarMaxSpeed(200);
	audi.GetInfo();

	return 0;
}