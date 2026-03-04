#include <iostream>
#include <windows.h>

extern "C" {
	__declspec(dllexport) void onPreStartup() {
		OutputDebugStringA("First CML mod for LCE!\n");
	}
}
