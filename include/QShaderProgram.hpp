#pragma once

class QShaderProgram {
protected:
	unsigned int id;
	QShaderProgram();
public:
	static QShaderProgram* load(const char* vshFile, const char* fshFile);
	void use();
};
