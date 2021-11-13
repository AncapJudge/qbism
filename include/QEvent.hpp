#pragma once

class GLFWwindow;

class QEvent {
protected:
	static QEvent* instance;
	static const int KEYBOARD_KEYS_COUNT = 256;
	static const int MOUSE_KEYS_COUNT = 8;

	bool keyState[KEYBOARD_KEYS_COUNT];
	bool mouseState[MOUSE_KEYS_COUNT];

	int mouseDeltaX;
	int mouseDeltaY;
	
	int mouseX;
	int mouseY;

	unsigned int keyHits[KEYBOARD_KEYS_COUNT];
	unsigned int mouseHits[MOUSE_KEYS_COUNT];
	
	bool mouseLocked;

	QEvent();
public:

	static QEvent* getInstance();

	void init();

	static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouseButtonCallback(GLFWwindow* window, int key, int action, int mode);
	static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);

	unsigned int keyHit(unsigned char scanCode);
	bool keyDown(unsigned char scanCode);
	
	unsigned int mouseHit(unsigned char button);
	bool mouseDown(unsigned char button);

	void lockMouse();
	void unlockMouse();

	bool isMouseLocked();
	
	void getMouseDelta(int* deltaX, int* deltaY);
	void flushKeyboard();
	void flushMouse();

	void pollEvents();
};
