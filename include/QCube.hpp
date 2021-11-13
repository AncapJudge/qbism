#pragma once

class QShaderProgram;

class QCube {
protected:
	QShaderProgram* shaderProgram;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
public:
	QCube();
	void draw();

	void setShaderProgram(QShaderProgram* shaderProgram);
	QShaderProgram* getShaderProgram();
};
