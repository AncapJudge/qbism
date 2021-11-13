#pragma once

class QApplication {
protected:
	static QApplication* instance;
	QApplication();
public:
	static QApplication* getInstance();
	int run();
};
