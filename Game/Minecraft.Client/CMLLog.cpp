#include "stdafx.h"

#include <windows.h>
#include <iostream>
#include <string>

#include "CMLLog.h"

void debugPrint(const std::string& msg) {
	OutputDebugStringA(msg.c_str());
}
