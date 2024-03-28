#include <iostream>
#include <string>
#include <math.h>


struct point {
    float x;
    float y;
    point (float x_ = 0.0f, float y_ = 0.0f) : x(x_), y(y_) {} //default consttructor
};



//abstract class common interface
class Shape {

public:
    void draw() const;
    void place(point const&);
    void rotate(point const&, double degree);

};

class Circle{

private:
    point position;
    float radius;

public:

    Circle (point pos_ = {0,0}, float radius_ = 1) : position(pos_), radius(radius_) {}

    void setRadius(float radius_) { radius = radius_; }
    float getRadius(){ return radius; }

    void draw(){

        std::cout << "Circle is drawn at: " << std::endl;
        std::cout << position.x << " , " << position.y << " with radius of " << radius << std::endl << std::endl;

    }
    void place (point const& pos_){
        position.x = pos_.x;
        position.y = pos_.y;
        std::cout << "Circle is placed at: " << position.x << " , " << position.y << std::endl << std::endl;
    }

};


class Rectangle : public Shape{

/*
    c - center,
    h - height, 
    w - width

*/

private:

    point position;

    double height;
    double width;

    double const half_height = height * 0.5;
    double const half_width = width * 0.5;

    point top_left;
    point top_right;
    point bottom_left;
    point bottom_right;

 
public:

    Rectangle (point pos_ = {0,0}, double height_ = 1, double width_ = 1)
                : position(pos_), height(height_), width(width_) {}


    double getHeight(){ return height; }
    double getWidth() {return width; }

    void draw(){

        std::cout << "Rectangle is drawn at: " << std::endl << std::endl;
        std::cout << top_left.x << " , " << top_left.y;
        std::cout << "\t\t\t" << top_right.x << " , " << top_right.y << std::endl;
        std::cout << bottom_left.x << " , " << bottom_left.y;
        std::cout << "\t\t\t" << bottom_right.x << " , " << bottom_right.y << std::endl << std::endl;


    }
    
    void place (point const& pos_){

        position.x = pos_.x;
        position.y = pos_.y;
        
        top_left.x = pos_.x - half_width;
        top_left.y = pos_.y + half_height;
        
        bottom_left.x = pos_.x - half_width;
        bottom_left.y = pos_.y - half_height;

        top_right.x = pos_.x + half_width;
        top_right.y = pos_.y + half_height;

        bottom_right.x = pos_.x + half_width;
        bottom_right.y = pos_.y - half_height;

        std::cout << "Rectangle is placed at: " << position.x << " / " << position.y << std::endl << std::endl;
        
    }

};



int main(){

    system("cls");
    // point p;

    // std::cout << "default p\n";
    // std::cout << "p.x = " << p.x << std::endl;
    // std::cout << "p.y = " << p.y << std::endl;

    // p.x = 7.3f;
    // p.y = 5.6f;

    // std::cout << "after p gets new values\n";
    // std::cout << "p.x = " << p.x << std::endl;
    // std::cout << "p.y = " << p.y << std::endl;

    Rectangle rect({0,0}, 2, 3);
    Circle cir;

    
    rect.place({-2.2,3.5});
    rect.draw();

    cir.place({1,1});
    cir.draw();

    return 0;

}   