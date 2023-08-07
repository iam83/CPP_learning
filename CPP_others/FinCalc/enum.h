#pragma once


/*
    Colors in Console both in OSX and WIN

                            Foreground      Background

        Black               30m	            40m
        Red                 31m	            41m
        Green               32m	            42m
        Yellow              33m	            43m
        Blue                34m	            44m
        Magenta             35m	            45m
        Cyan                36m	            46m
        Light gray          37m	            47m
        Dark gray           90m	            100m
        Light red           91m	            101m
        Light green         92m	            102m
        Light yellow        93m	            103m
        Light blue          94m	            104m
        Light magenta       95m	            105m
        Light cyan          96m	            106m
        White               97m	            107m
        Bold	            1m	            -
        Underline	        4m	            -
        No underline	    24m	            -
        Negative(reverse
        the foreground
        and background)	    7m	-
        Positive(no negative27m	-
        Default	            0m	-


        std::cout << "\033[1;31mBold red text\033[0m\n";

*/


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



