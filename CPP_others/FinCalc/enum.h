#pragma once

<<<<<<< HEAD
//windows console colors
enum ConsoleColor{
=======
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

#ifdef _WIN32
//windows console
enum CColor{
>>>>>>> 8579c96a31411db3431cc52df729d58dadbf5211
    DeepCyan = 3,
    DarkRed = 4,
    NormalWhite = 7,
    Grey = 8,
    Blue = 9,
    Green = 10,
    Red = 12,
    Yellow = 14,
};
#endif

#ifdef __APPLE__
//OSX terminal
enum CColor{
    Reset     =   0,
    Black     =  30,
    Red       =  31,
    Green     =  32,
    Yellow    =  33,
    Blue      =  34,
    Magenta   =  35,
    Cyan      =  36,
    White     =  37,
};
#endif



