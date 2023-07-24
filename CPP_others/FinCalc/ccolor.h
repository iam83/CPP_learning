#pragma once
#include "enum.h"
#include <windows.h>

#ifdef __APPLE_
std::string setColor(CColor color); //returns string with color Code for OSX
#endif

#ifdef _WIN32
void setColor(HANDLE& handle, CColor color);
#endif