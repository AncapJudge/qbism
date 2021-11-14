#include <QCube.hpp>
#include <GL/glew.h>
#include <iostream>
#include <QShaderProgram.hpp>
#include <QEvent.hpp>

QCube::QCube() {
	GLfloat vertices[] = {
		//position				// normal				// UV
		0.0f, 0.0f,  1.0f,	 0.0f,  0.0f,  1.0f,	0.75f, 0.5f,
		0.0f,  1.0f,  1.0f,	 0.0f,  0.0f,  1.0f,	0.75f, 0.25f,
		 1.0f,  1.0f,  1.0f,	 0.0f,  0.0f,  1.0f,	1.0f,  0.25f,
		 1.0f, 0.0f,  1.0f,	 0.0f,  0.0f,  1.0f,	1.0f,  0.5f,

		1.0f, 0.0f,  1.0f,		 1.0f,  0.0f,  0.0f,	0.25f, 0.5f,
		1.0f,  1.0f,  1.0f,		 1.0f,  0.0f,  0.0f,	0.25f, 0.25f,
		1.0f,  1.0f, 0.0f,		 1.0f,  0.0f,  0.0f,	0.5f,  0.25f,
		1.0f, 0.0f, 0.0f,		 1.0f,  0.0f,  0.0f,	0.5f,  0.5f,

		 1.0f, 0.0f, 0.0f,	 0.0f,  0.0f, -1.0f,	0.5f,  0.5f,
		 1.0f,  1.0f, 0.0f,	 0.0f,  0.0f, -1.0f,	0.5f,  0.25f,
		0.0f,  1.0f, 0.0f,	 0.0f,  0.0f, -1.0f,	0.75f, 0.25f,
		0.0f, 0.0f, 0.0f,	 0.0f,  0.0f, -1.0f,	0.75f, 0.5f,

		0.0f, 0.0f,  1.0f,	-1.0f,  0.0f,  0.0f,	0.25f, 0.5f,
		0.0f, 0.0f, 0.0f,	-1.0f,  0.0f,  0.0f,	0.0f,  0.5f,
		0.0f,  1.0f, 0.0f,	-1.0f,  0.0f,  0.0f,	0.0f,  0.25f,
		0.0f,  1.0f,  1.0f,	-1.0f,  0.0f,  0.0f,	0.25f, 0.25f,

		0.0f, 0.0f,  1.0f,	 0.0f, -1.0f,  0.0f,	0.25f, 0.5f,
		 1.0f, 0.0f,  1.0f,	 0.0f, -1.0f,  0.0f,	0.5f,  0.5f,
		 1.0f, 0.0f, 0.0f,	 0.0f, -1.0f,  0.0f,	0.5f,  0.75f,
		0.0f, 0.0f, 0.0f,	 0.0f, -1.0f,  0.0f,	0.25f, 0.75f,

		0.0f,  1.0f, 0.0f,	 0.0f,  1.0f,  0.0f,	0.25f, 0.0f,
		 1.0f,  1.0f, 0.0f,	 0.0f,  1.0f,  0.0f,	0.5f,  0.0f,
		 1.0f,  1.0f,  1.0f,	 0.0f,  1.0f,  0.0f,	0.5f,  0.25f,
		0.0f,  1.0f,  1.0f, 	 0.0f,  1.0f,  0.0f,	0.25f, 0.25f
    };
    GLuint indices[] = {  // Note that we start from 0!
         0,  1,  2,   0,  2,  3,
		 4,  5,  6,   4,  6,  7,
		 8,  9, 10,   8, 10, 11,
		12, 13, 14,  12, 14, 15,
		16, 17, 18,  16, 18, 19,
		20, 21, 22,  20, 22, 23
    };
	
	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
}

void QCube::draw() {
	shaderProgram->use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void QCube::setShaderProgram(QShaderProgram* shaderProgram) {
	this->shaderProgram = shaderProgram;
}

QShaderProgram* QCube::getShaderProgram() {
	return shaderProgram;
}