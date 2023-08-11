/*

    Set console colors

*/

#include <string>
#include "ccolor.h"

std::string setColor(CColor color){

    switch(color) {
        case CColor::Reset: return "\033[0m"; break;
        case CColor::Bold: return "\033[1m"; break;
        case CColor::Underline: return "\033[4m"; break;
        case CColor::Negative: return "\033[7m"; break;
        case CColor::NoUnderine: return "\033[24m"; break;
        case CColor::Positive: return "\033[27m"; break;
        case CColor::Black: return "\033[30m"; break;
        case CColor::Red: return "\033[31m"; break;
        case CColor::Green: return  "\033[32m"; break;
        case CColor::Yellow: return  "\033[33m"; break;
        case CColor::Blue: return "\033[34m"; break;
        case CColor::Magenta: return "\033[35m"; break;
        case CColor::Cyan: return "\033[36m"; break;
        case CColor::LightGrey: return "\033[37m"; break;
        case CColor::BG_Black: return "\033[40m"; break;
        case CColor::BG_Red: return "\033[41m"; break;
        case CColor::BG_Green: return "\033[42m"; break;
        case CColor::BG_Yellow: return "\033[43m"; break;
        case CColor::BG_Blue: return "\033[44m"; break;
        case CColor::BG_Magenta: return "\033[45m"; break;
        case CColor::BG_Cyan: return "\033[46m"; break;
        case CColor::BG_LightGrey: return "\033[47m"; break;
        case CColor::DarkGrey: return "\033[90m"; break;
        case CColor::LightRed: return "\033[91m"; break;
        case CColor::LightGreen: return "\033[92m"; break;
        case CColor::LightYellow: return "\033[93m"; break;
        case CColor::LightBlue: return "\033[94m"; break;
        case CColor::LightMagenta: return "\033[95m"; break;
        case CColor::LightCyan: return "\033[96m"; break;
        case CColor::White: return "\033[97m"; break;
        case CColor::BG_LightRed: return "\033[101m"; break;
        case CColor::BG_LightGreen: return "\033[102m"; break;
        case CColor::BG_LightYellow: return "\033[103m"; break;
        case CColor::BG_LightBlue: return "\033[104m"; break;
        case CColor::BG_LightMagenta: return "\033[105m"; break;
        case CColor::BG_LightCyan: return "\033[106m"; break;
        case CColor::BG_White: return "\033[107m"; break;
        default: return "\033[0m";
    }
}


