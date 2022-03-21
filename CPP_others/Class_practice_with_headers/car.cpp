#include "car.h"
#include <iostream>

Car::Car(std::string _name, std::string _color, double _speed) {

	name = _name;
	color = _color;
	speed = _speed;

}

void Car::SetSpeed(double _speed) {
	speed = _speed;
}

void Car::SetName(std::string _name) {
	name = _name;
}

void Car::SetColor(std::string color) {
	this->color = color;
}

void Car::GetInfo() {

	std::cout << "Name: " << name << std::endl;
	std::cout << "Color: " << color << std::endl;
	std::cout << "Speed: " << speed << std::endl;
	std::cout << std::endl;
}
