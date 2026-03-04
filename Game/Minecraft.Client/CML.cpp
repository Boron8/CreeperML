#include "stdafx.h"

#include "CML.h"
#include <windows.h>
#include <iostream>
#include <string>

#include "CMLLog.h"


CML::CML() {
	// init
}

void CML::loadMods(const std::string& folder) {
	debugPrint("[CML]: Loading mods...\n");
	
	std::string searchPath = folder + "\\*.dll";

	WIN32_FIND_DATA findData;
	HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

	if (hFind == INVALID_HANDLE_VALUE) {
		debugPrint("[CML]: Invalid hFind handle value.\n");
		return;
	}

	do {
		std::string fullPath = folder + "\\" + findData.cFileName;

		HMODULE module = LoadLibraryA(fullPath.c_str());
		if (!module) {
			continue;
		}
		
		m_modules.push_back(module);

		ModFn onPreStartup = (ModFn)GetProcAddress(module, "onPreStartup");

		if (onPreStartup) {
			m_onPreStartupList.push_back(onPreStartup);
		}

		debugPrint("[CML]: Loaded mod: " + std::string(findData.cFileName) + "\n");
	} while (FindNextFileA(hFind, &findData));

	FindClose(hFind);
}

void CML::callOnPreStartup() {
	for (size_t i = 0; i < m_onPreStartupList.size(); ++i) {
		m_onPreStartupList[i]();
	}
}

CML::~CML() {
	for (size_t i = 0; i < m_modules.size(); ++i) {
		FreeLibrary(m_modules[i]);
	}

	m_modules.clear();
	m_onPreStartupList.clear();
}
