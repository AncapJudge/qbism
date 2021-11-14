#include <iostream>
#include <QWindow.hpp>
#include <QColor.hpp>
#include <QEvent.hpp>
#include <QCube.hpp>
#include <QShaderProgram.hpp>
#include <QFile.hpp>

int main() {
	QWindow* window = QWindow::getInstance();
	if (!window->open(800, 600, "QBism test")) {
		return -1;
	}
	window->setClearColor(QColor(0.2f, 0.3f, 0.15f));
	
	QCube* cube = new QCube();
	QShaderProgram* shaderProgram = QShaderProgram::load("./assets/shader.glslv", "./assets/shader.glslf");
	cube->setShaderProgram(shaderProgram);

	QEvent* ev_in = QEvent::getInstance();
	do {
		window->clear();
		ev_in->pollEvents();
		cube->draw();
		window->swapBuffers();
	} while(window->isOpen());

	window->termitate();
    return 0;
}
