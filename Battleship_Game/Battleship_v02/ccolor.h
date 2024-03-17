#pragma once

enum CColor{
    Reset               =   0,
    Bold                =   1,
    Underline           =   4,
    Negative            =   7,
    NoUnderine          =  24,
    Positive            =  27,
    Black               =  30,
    Red                 =  31,
    Green               =  32,
    Yellow              =  33,
    Blue                =  34,
    Magenta             =  35,
    Cyan                =  36,
    LightGrey           =  37,
    BG_Black            =  40,
    BG_Red              =  41,
    BG_Green            =  42,
    BG_Yellow           =  43,
    BG_Blue             =  44,
    BG_Magenta          =  45,
    BG_Cyan             =  46,
    BG_LightGrey        =  47,
    DarkGrey            =  90,
    LightRed            =  91,
    LightGreen          =  92,
    LightYellow         =  93,
    LightBlue           =  94,
    LightMagenta        =  95,
    LightCyan           =  96,
    White               =  97,
    BG_LightRed         = 101,
    BG_LightGreen       = 102,
    BG_LightYellow      = 103,
    BG_LightBlue        = 104,
    BG_LightMagenta     = 105,
    BG_LightCyan        = 106,
    BG_White            = 107
};


std::string setColor(CColor color); //returns string with color Code for OSX