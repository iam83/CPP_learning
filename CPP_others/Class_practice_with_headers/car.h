#pragma once

#include <string>
#include <iostream>

class Car
{
private:
	std::string name;
	std::string color;
	double speed;

public:

	Car (std::string name, std::string color, double speed);
	void SetSpeed(double speed);
	void SetName(std::string name);
	void SetColor(std::string color);
	void GetInfo();

};

