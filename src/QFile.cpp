#include <QFile.hpp>
#include <fstream>
#include <streambuf>
#include <iostream>
std::string QFile::readToString(const char* path) {
	std::ifstream t(path);
	std::string str((std::istreambuf_iterator<char>(t)),
					std::istreambuf_iterator<char>());
	return str;
}