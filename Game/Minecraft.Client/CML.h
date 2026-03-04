#pragma once

#include <Windows.h>
#include <vector>
#include <string>

typedef void (*ModFn)();

class CML {
public:
	static CML& getInstance() {
		static CML instance;
		return instance;
	}

	void loadMods(const std::string& folder);

	void callOnPreStartup();

private:
	CML();
	~CML();
	CML(const CML&);
	CML& operator=(const CML&);

	std::vector<HMODULE> m_modules;

	std::vector<ModFn> m_onPreStartupList;
};
