#pragma once
#include <map>

class QShaderProgram {
protected:
	unsigned int id;
	QShaderProgram();
	std::map<const char*, unsigned int> uniformIds;

public:
	static QShaderProgram* load(const char* vshFile, const char* fshFile);
	void use();
	
	void uniformMatrix(const char* uniform_name, void* matrix);
};
