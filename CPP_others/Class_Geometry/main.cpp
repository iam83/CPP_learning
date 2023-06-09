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
        //std::cout << "Box constuctor has been constracted\n\n";
    }
    
    ~Box(){
        //std::cout << "Box destructor\n\n";
    }

    void print() {
        std::cout << "Length: " << length << '\n'
                  << "Width: "  << width  << '\n'
                  << "Height: " << height << '\n' << '\n';
    }

     bool isEqual(Box &b){
        return (length == b.length && width == b.width && height == b.height);
    }

};

int main(){

    Box box1;
    Box box2(20);
    Box box3(10, 10, 10);
    Box box4(1, 1, 1);

    box1.print();
    box2.print();
    box3.print();
    box4.print();

    if (box1.isEqual(box2))
        std::cout << "box1 and box2 are equal\n";
    else
        std::cout << "box1 and box2 are not equal\n";
    


    return 0;

}