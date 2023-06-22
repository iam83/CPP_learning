/*

        Colors in OSX Terminal
        
                foreground background
        black        30         40
        red          31         41
        green        32         42
        yellow       33         43
        blue         34         44
        magenta      35         45
        cyan         36         46
        white        37         47


        reset             0  (everything back to normal)
        bold/bright       1  (often a brighter shade of the same colour)
        underline         4
        inverse           7  (swap foreground and background colours)
        bold/bright off  21
        underline off    24
        inverse off      27

        example:
        std::cout << "\033[1;31mBold red text\033[0m\n";
*/


#include <iostream>
#include <array>

enum Color{
    black   =     30,
    red     =     31,
    green   =     32,
    yellow  =     33,
    blue    =     34,
    magenta =     35,
    cyan    =     36,
    white   =     37
};


int main(){

    std::array<int, 7> bg_color {0, 1, 4, 7, 21, 24, 27};

    for (int i = 0; i < 8; ++i){

        std::cout << "Color " << i << "      " << "\033[3" << i << "m"  << "Hello!!!" << "\033[0m\n";

    }

    std::cout << "\n";

    for (int i = 0; i < 7; ++i){

        std::cout << "Color " << bg_color[i] << "      " << "\033[" << bg_color[i] << ";3" << i << "m"  << "Hello!!!" << "\033[0m\n";

    }

    return 0;
}