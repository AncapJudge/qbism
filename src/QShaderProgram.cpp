#include <QShaderProgram.hpp>
#include <GL/glew.h>
#include <string>
#include <QFile.hpp>
#include <iostream>
#include <stdexcept>

QShaderProgram::QShaderProgram() = default;

QShaderProgram* QShaderProgram::load(const char* vshFile, const char* fshFile) {
	QShaderProgram* program = new QShaderProgram();

	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	std::string vertexShaderSource = QFile::readToString(vshFile);
	const GLchar* vShaderCode = vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);

	glCompileShader(vertexShader);

	GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		throw new std::runtime_error("Vertex shader compilation error");
    }

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmentShaderSource = QFile::readToString(fshFile);
	const GLchar* fShaderCode = fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		throw new std::runtime_error("Fragment shader compilation error");
    }

	program->id = glCreateProgram();
	glAttachShader(program->id, vertexShader);
	glAttachShader(program->id, fragmentShader);
	glLinkProgram(program->id);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}

void QShaderProgram::use() {
	glUseProgram(id);
}

void QShaderProgram::uniformMatrix(const char* uniformName, void* matrix) {
	GLuint uniformId;
	if (!uniformIds[uniformName]) {
		uniformId = glGetUniformLocation(id, uniformName);
		uniformIds.insert(std::pair<const char*, unsigned int>(uniformName, 10));
	}
	uniformId = uniformIds[uniformName];
	glUniformMatrix4fv(uniformId, 1, GL_FALSE, (GLfloat*)matrix);
}