#include <QChunkMesh.hpp>
#include <GL/glew.h>
#include <QShaderProgram.hpp>
#include <QTexture.hpp>
#include <iostream>
#define VERTEX_SIZE 6

#define VERTEX(INDEX, X,Y,Z, U,V, L) facesData[INDEX+0] = (X);\
								  facesData[INDEX+1] = (Y);\
								  facesData[INDEX+2] = (Z);\
								  facesData[INDEX+3] = (U);\
								  facesData[INDEX+4] = (V);\
								  facesData[INDEX+5] = (L);\
								  INDEX += VERTEX_SIZE;

QChunkMesh::QChunkMesh(): VBO(0), VAO(0), EBO(0) {
	elementsCount = 0;

	facesCount = 0;
}

void QChunkMesh::updateMesh(QChunk* chunk) {
	// facesData.clear();
	// elementsData.clear();
	this->elementsCount = 0;

	this->facesCount = 0;
	const unsigned int meshSize = CHUNK_WIDTH*CHUNK_HEIGHT*CHUNK_LENGTH*VERTEX_SIZE*24;
	float* facesData =  new float [meshSize];
	unsigned int* elementsData = new unsigned int[CHUNK_WIDTH*CHUNK_HEIGHT*CHUNK_LENGTH*36];

	unsigned int index = 0;
	unsigned int vertex_index = 0;

	for (int x = 0; x < CHUNK_WIDTH; x++) {
		for (int y = 0; y < CHUNK_HEIGHT; y++) {
			for (int z = 0; z < CHUNK_LENGTH; z++) {
				if (chunk->data(x, y, z) != 0) {
					// front
					float l = 0.90f;

					VERTEX(index, x + 1.0f, y + 0.0f, z + 1.0f, 1.0f,  0.5f, l);
					VERTEX(index, x + 1.0f, y + 1.0f, z + 1.0f, 1.0f,  0.25f, l);
					VERTEX(index, x + 0.0f, y + 1.0f, z + 1.0f, 0.75f, 0.25f, l);
					VERTEX(index, x + 0.0f, y + 0.0f, z + 1.0f, 0.75f, 0.5f, l);
					
					unsigned int frontE[] = {
						vertex_index + 0,
						vertex_index + 1,
						vertex_index + 2,
						vertex_index + 0,
						vertex_index + 2,
						vertex_index + 3,
					};

					for (int i = 0; i < 6; i++)
						elementsData[elementsCount+i] = frontE[i];
					elementsCount += 6;
					vertex_index += 4;
					
					// rear
					l = 0.80f;
					VERTEX(index, x + 0.0f, y + 0.0f, z + 0.0f,	 0.75f, 0.5f, l);
					VERTEX(index, x + 0.0f, y + 1.0f, z + 0.0f,	 0.75f, 0.25f, l);
					VERTEX(index, x + 1.0f, y + 1.0f, z + 0.0f,	 0.5f,  0.25f, l);
					VERTEX(index, x + 1.0f, y + 0.0f, z + 0.0f,	 0.5f,  0.5f, l);
					

					unsigned int rearE[] = {
						vertex_index + 0,
						vertex_index + 1,
						vertex_index + 2,
						vertex_index + 0,
						vertex_index + 2,
						vertex_index + 3,
					};

					for (int i = 0; i < 6; i++)
						elementsData[elementsCount+i] = rearE[i];
					elementsCount += 6;
					vertex_index += 4;

					// left
					l = 0.85f;
					VERTEX(index, x + 0.0f, y + 1.0f, z + 1.0f,	 0.25f, 0.25f, l);
					VERTEX(index, x + 0.0f, y + 1.0f, z + 0.0f,	 0.0f,  0.25f, l);
					VERTEX(index, x + 0.0f, y + 0.0f, z + 0.0f,	 0.0f,  0.5f, l);
					VERTEX(index, x + 0.0f, y + 0.0f, z + 1.0f,	 0.25f, 0.5f, l);
					

					unsigned int leftE[] = {
						vertex_index + 0,
						vertex_index + 1,
						vertex_index + 2,
						vertex_index + 0,
						vertex_index + 2,
						vertex_index + 3,
					};
					
					for (int i = 0; i < 6; i++)
						elementsData[elementsCount+i] = leftE[i];
					elementsCount += 6;
					vertex_index += 4;


					// right
					l = 0.85f;
					VERTEX(index, x + 1.0f, y + 0.0f, z + 0.0f,	 0.5f,  0.5f, l);
					VERTEX(index, x + 1.0f, y + 1.0f, z + 0.0f,	 0.5f,  0.25f, l);
					VERTEX(index, x + 1.0f, y + 1.0f, z + 1.0f,	 0.25f, 0.25f, l);
					VERTEX(index, x + 1.0f, y + 0.0f, z + 1.0f,	 0.25f, 0.5f, l);

					unsigned int rightE[] = {
						vertex_index + 0,
						vertex_index + 1,
						vertex_index + 2,
						vertex_index + 0,
						vertex_index + 2,
						vertex_index + 3,
					};
					for (int i = 0; i < 6; i++)
						elementsData[elementsCount+i] = rightE[i];
					elementsCount += 6;
					vertex_index += 4;


					// top
					l = 1.0f;
					VERTEX(index, x + 0.0f, y + 1.0f, z + 1.0f,	0.25f, 0.25f, l);
					VERTEX(index, x + 1.0f, y + 1.0f, z + 1.0f,	0.5f,  0.25f, l);
					VERTEX(index, x + 1.0f, y + 1.0f, z + 0.0f,	0.5f,  0.0f, l);
					VERTEX(index, x + 0.0f, y + 1.0f, z + 0.0f,	0.25f, 0.0f, l);

					unsigned int topE[] = {
						vertex_index + 0,
						vertex_index + 1,
						vertex_index + 2,
						vertex_index + 0,
						vertex_index + 2,
						vertex_index + 3,
					};
					for (int i = 0; i < 6; i++)
						elementsData[elementsCount+i] = topE[i];
					elementsCount += 6;
					vertex_index += 4;


					// bottom
					l = 0.6f;
					VERTEX(index, x + 0.0f, y + 0.0f, z + 0.0f,	 0.25f, 0.75f, l);
					VERTEX(index, x + 1.0f, y + 0.0f, z + 0.0f,	 0.5f,  0.75f, l);
					VERTEX(index, x + 1.0f, y + 0.0f, z + 1.0f,	 0.5f,  0.5f, l);
					VERTEX(index, x + 0.0f, y + 0.0f, z + 1.0f,	 0.25f, 0.5f, l);
					
					unsigned int bottomE[] = {
						vertex_index + 0,
						vertex_index + 1,
						vertex_index + 2,
						vertex_index + 0,
						vertex_index + 2,
						vertex_index + 3,
					};
					for (int i = 0; i < 6; i++)
						elementsData[elementsCount+i] = bottomE[i];
					elementsCount += 6;
					vertex_index += 4;


				}
			}
		}
	}


	
	if (VAO == 0) {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
	}

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * meshSize, facesData, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * elementsCount, elementsData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

	delete[] facesData;
	delete[] elementsData;
	// glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

}

void QChunkMesh::draw() {
	shaderProgram->use();
	
	if (texture != nullptr) {
		glBindTexture(GL_TEXTURE_2D, texture->getId());
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, elementsCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void QChunkMesh::setShaderProgram(QShaderProgram* shaderProgram) {
	this->shaderProgram = shaderProgram;
}

QShaderProgram* QChunkMesh::getShaderProgram() {
	return shaderProgram;
}

void QChunkMesh::setTexture(QTexture* texture) {
	this->texture = texture;
}

QTexture* QChunkMesh::getTexture() {
	return texture;
}