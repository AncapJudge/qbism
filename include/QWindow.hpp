#pragma once
#include <QColor.hpp>

class GLFWwindow;

class QWindow {
protected:
	QWindow();
	GLFWwindow* glfwWindow;
	static QWindow* instance;

public:
	static QWindow* getInstance();
	bool open(unsigned int width, unsigned int height, const char* title);
	bool isOpen();
	void termitate();
	void swapBuffers();

	void setClearColor(QColor color);
	void clear();

	GLFWwindow* getGLFWwindow();
};
