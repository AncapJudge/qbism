#include <QApplication.hpp>

QApplication* QApplication::instance = nullptr;

QApplication::QApplication() = default;

QApplication* QApplication::getInstance() {
	if (instance == nullptr) {
		instance = new QApplication();
	}

	return instance;
}

int QApplication::run() {
	return 0;
}