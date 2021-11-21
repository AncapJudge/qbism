#pragma once
#include <vector>
#include <QChunk.hpp>

class QShaderProgram;
class QTexture;



class QChunk;

class QChunkMesh {
protected:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	
	unsigned int elementsCount;
	unsigned int facesCount;
	QShaderProgram* shaderProgram;
	QTexture* texture;
	
public:
	QChunkMesh();
	void updateMesh(QChunk* chunk);
	void draw();

	void setShaderProgram(QShaderProgram* shaderProgram);
	QShaderProgram* getShaderProgram();

	void setTexture(QTexture* texture);
	QTexture* getTexture();
};
