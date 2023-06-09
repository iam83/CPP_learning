#include <iostream>


class Box{

public:
    double length;
    double width;
    double height;
    
    //create default constructor
    Box(double l = 10, double w = 10, double h = 10)
        : length(l), width(w), height(h)
    {    
    }
    

    void print() {
        std::cout << "Length: " << length << '\n'
                << "Width: " << width << '\n'
                << "Height: " << height << '\n' << '\n';
    }

int main(){

    Box box1;

    Box box2(20);

    box1.print();
    box2.print();

    return 0;

}