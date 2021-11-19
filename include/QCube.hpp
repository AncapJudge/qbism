#pragma once

class QShaderProgram;
class QTexture;

class QCube {
protected:
	QShaderProgram* shaderProgram;
	QTexture* texture;
	
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
public:
	QCube();
	void draw();

	void setShaderProgram(QShaderProgram* shaderProgram);
	QShaderProgram* getShaderProgram();

	void setTexture(QTexture* texture);
	QTexture* getTexture();
};
