#include <QWindow.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <QEvent.hpp>

QWindow* QWindow::instance = nullptr;

QWindow::QWindow() = default;

QWindow* QWindow::getInstance() {
	if (instance == nullptr) {
		instance = new QWindow();
	}

	return instance;
}

bool QWindow::open(unsigned int width, unsigned int height, const char* title) {
	if (!glfwInit()) {
		std::cout << "Cannot initialize GLFW\n";
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 0);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (window == NULL) {
		std::cout << "Cannot create window\n";
		glfwTerminate();
		return false;
	}
	else {
		glfwWindow = window;
	}

	glfwMakeContextCurrent(glfwWindow);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "Cannot initialize GLEW\n";
		return false;
	}

	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	return true;
}

bool QWindow::isOpen() {
	return glfwWindowShouldClose(glfwWindow) == 0;
}

void QWindow::swapBuffers() {
	glfwSwapBuffers(glfwWindow);
}

void QWindow::termitate() {
	glfwTerminate();
}

void QWindow::setClearColor(QColor color) {
	glClearColor(
		color.red,
		color.green,
		color.blue,
		color.alpha
	);
}

void QWindow::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLFWwindow* QWindow::getGLFWwindow() {
	return glfwWindow;
}