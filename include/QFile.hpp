#pragma once
#include <string>

class QFile {
public:
	static std::string readToString(const char* path);
};
