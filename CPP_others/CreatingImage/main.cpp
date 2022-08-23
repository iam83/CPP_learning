#include <iostream>
#include <fstream>

int main(){

    std::ofstream image;
    image.open("image.ppm");

    if (image.is_open()){
        //place header info

        image << "P3" << std::endl;
        image << "350 350" << std::endl;
        image << "255" << std::endl;

        for (int y = 0; y < 350; y++){
            for (int x = 0; x < 350; x++){
                image << y << " " << x << " " << x << std::endl;
            }
        }
    }

    image.close();

    return 0;
}