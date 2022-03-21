#include <iostream>


// enum class используются для удобства

enum class Days {
	Mon,
	Tue,
	Wed,
	Thu,
	Fri,
	Sat,
	Sun
};

int main() {

	Days day = Days::Sun;

	if (day == Days::Sat || day == Days::Sun) {

		std::cout << "It's weekend" << std::endl;
	}
	else {
		std::cout << "It's a working day" << std::endl;
	}


	return 0;

}