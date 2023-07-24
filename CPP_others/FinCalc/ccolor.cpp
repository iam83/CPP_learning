/*

    Set console colors

*/

#include "enum.h"
#include <string>
#include <windows.h>
#include <iostream>

#ifdef __APPLE__
std::string setColor(CColor color){

    switch(color) {
        case CColor::Black: return "\033[30m"; break;
        case CColor::Red: return "\033[31m"; break;
        case CColor::Green: return  "\033[32m"; break;
        case CColor::Yellow: return  "\033[33m"; break;
        case CColor::Blue: return "\033[34m"; break;
        case CColor::Magenta: return "\033[35m"; break;
        case CColor::Cyan: return "\033[36m"; break;
        case CColor::White: return "\033[37m"; break;
        case CColor::Reset: return "\033[0m"; break;
        default: return "\033[0m";
    }
}
#endif

#ifdef _WIN32
void setColor(HANDLE& handle, CColor color){
    
    switch(color) {    
        case CColor::Red: SetConsoleTextAttribute(handle, CColor::Red); break;
        case CColor::Green: SetConsoleTextAttribute(handle, CColor::Green); break;
        case CColor::Yellow: SetConsoleTextAttribute(handle, CColor::Yellow); break;
        case CColor::Blue: SetConsoleTextAttribute(handle, CColor::Blue); break;
        case CColor::Cyan: SetConsoleTextAttribute(handle, CColor::Cyan); break;
        case CColor::DarkRed: SetConsoleTextAttribute(handle, CColor::DarkRed); break;
        case CColor::Reset: SetConsoleTextAttribute(handle, CColor::NormalWhite); break;
        case CColor::Grey: SetConsoleTextAttribute(handle, CColor::Grey); break;
        default: SetConsoleTextAttribute(handle, CColor::Grey); break;
    }
}

#endif