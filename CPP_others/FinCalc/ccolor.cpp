/*

    Set console colors

*/

#include "enum.h"
#include <string>

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
std::string setColor(CColor color){

    switch(color) {
        case CColor::Red: return "\033[31m"; break;
        case CColor::Green: return "\033[32m"; break;
        case CColor::Yellow: return "\033[33m"; break;
        case CColor::Blue: return "\033[34m"; break;
        case CColor::Magent: return "\033[35m"; break;
        case CColor::Cyan: return "\033[36m"; break;
        case CColor::White:return "\033[37m"; break;
        case CColor::Reset:return "\033[0m"; break;
    }

    return resultColor;
}
#endif