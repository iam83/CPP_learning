#include <iostream>


struct Transform(){
    
    struct Location(){
        double x, y, z;
    };
    struct Rotation(){
        double x, y, z;
    };

    struct Scale(){
        dobule x, y, z;
    };

}


int main(){

    Transform Sphere;

    Sphere.Location = {10, 10, 10};
    Sphere.Rotation = {0, 0, 0};
    Sphere.Scale = {1, 1, 1};

    std::cout << "Sphere: " << "x = " << x << ", " << "y = " << y << ", " << "z = " << z << ".\n";

}