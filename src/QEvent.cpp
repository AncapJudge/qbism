#include <QEvent.hpp>
#include <GLFW/glfw3.h>
#include <QWindow.hpp>
#include <string.h>
#include <iostream>

QEvent* QEvent::instance = nullptr;

QEvent::QEvent() = default;

QEvent* QEvent::getInstance() {
	if (instance == nullptr) {
		instance = new QEvent();
		instance->init();
	}

	return instance;
}

void QEvent::init() {
	GLFWwindow* glfwWindow = QWindow::getInstance()->getGLFWwindow();

	memset(keyState, false, KEYBOARD_KEYS_COUNT*sizeof(bool));
	memset(mouseState, false, MOUSE_KEYS_COUNT*sizeof(bool));

	glfwSetKeyCallback(glfwWindow, &QEvent::keyboardCallback);
	glfwSetMouseButtonCallback(glfwWindow, &QEvent::mouseButtonCallback);
	glfwSetCursorPosCallback(glfwWindow, &QEvent::mouseMoveCallback);

	flushMouse();
	flushKeyboard();
	mouseLocked = false;
}

void QEvent::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	QEvent* instance = QEvent::getInstance();
	if (action == GLFW_PRESS) {
		instance->keyState[scancode] = true;
	}
	else if (action == GLFW_RELEASE) {
		instance->keyState[scancode] = false;
	}

	if (action == GLFW_PRESS) {
		instance->keyHits[scancode]++;
	}
}

void QEvent::mouseButtonCallback(GLFWwindow* window, int key, int action, int mode) {
	QEvent* instance = QEvent::getInstance();
	instance->mouseState[key] = (action == GLFW_PRESS);

	if (action == GLFW_PRESS) {
		instance->mouseHits[key]++;
	}
}

void QEvent::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos) {
	QEvent* instance = QEvent::getInstance();

	instance->mouseDeltaX += xpos - instance->mouseX;
	instance->mouseDeltaY += ypos - instance->mouseY;

	if(instance->mouseLocked) {
		int width, height;
		glfwGetWindowSize(window, &width, &height);

		glfwSetCursorPos(window, width / 2, height / 2);
		instance->mouseX = width / 2;
		instance->mouseY = height / 2;
	}
	else {
		instance->mouseX = xpos;
		instance->mouseY = ypos;
	}
}

bool QEvent::keyDown(unsigned char scancode) {
	return keyState[scancode];
}

unsigned int QEvent::keyHit(unsigned char scancode) {
	unsigned int hits = keyHits[scancode];
	keyHits[scancode] = 0;
	return hits;
}

bool QEvent::mouseDown(unsigned char button) {
	return mouseState[button];
}

unsigned int QEvent::mouseHit(unsigned char button) {
	unsigned int hits = mouseHits[button];
	mouseHits[button] = 0;
	return hits;
}

void QEvent::getMouseDelta(int* deltaX, int* deltaY) {
	*deltaX = mouseDeltaX;
	*deltaY = mouseDeltaY;
	mouseDeltaX = 0;
	mouseDeltaY = 0;
}

void QEvent::lockMouse() {
	GLFWwindow* window = QWindow::getInstance()->getGLFWwindow();

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	glfwSetCursorPos(window, width / 2, height / 2);
	mouseX = width / 2;
	mouseY = height / 2;
	flushMouse();
	mouseLocked = true;
}

void QEvent::unlockMouse() {
	GLFWwindow* window = QWindow::getInstance()->getGLFWwindow();

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	mouseLocked = false;
}

bool QEvent::isMouseLocked() {
	return mouseLocked;
}

void QEvent::flushKeyboard() {
	memset(keyHits, 0, KEYBOARD_KEYS_COUNT*sizeof(unsigned int));
}

void QEvent::flushMouse() {
	memset(mouseHits, 0, MOUSE_KEYS_COUNT*sizeof(unsigned int));
	mouseDeltaX = 0;
	mouseDeltaY = 0;
}

void QEvent::pollEvents() {
	glfwPollEvents();
}