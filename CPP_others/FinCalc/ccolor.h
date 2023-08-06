#pragma once
#include "enum.h"


#ifdef __APPLE__
std::string setColor(CColor color); //returns string with color Code for OSX
#endif

#ifdef _WIN32
#include <windows.h>
void setColor(HANDLE& handle, CColor color);
#endif