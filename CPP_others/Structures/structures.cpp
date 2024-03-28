#include <iostream>

struct vec2 {

 	float x, y;
	vec2(float value) : x(value), y(value) {}
	vec2(float x_, float y_) : x(x_), y(y_) {}

	vec2 operator+(vec2 const& instance) {
        return vec2(x + instance.x, y + instance.y);
    }
	vec2 operator-(vec2 const& instance) { return vec2(x - instance.x, y - instance.y); }
	vec2 operator*(vec2 const& instance) { return vec2(x * instance.x, y * instance.y); }
	vec2 operator/(vec2 const& instance) { return vec2(x / instance.x, y / instance.y); }

};

int main(){

    vec2 temp (50);
    vec2 pointOne (10.0, 5.0);
    vec2 pointTwo (20.0, 10.0);

    vec2 result = pointOne * pointTwo;
    vec2 newPoint = result;

    std::cout << "result.x = " << result.x << std::endl;
    std::cout << "result.y = " << result.y << std::endl;

    std::cout << "newPoint.x = " << newPoint.x << std::endl;
    std::cout << "newPoint.y = " << newPoint.y << std::endl;

    std::cout << "temp.x = " << temp.x << std::endl;
    std::cout << "temp.y = " << temp.y << std::endl;

    return 0;
}