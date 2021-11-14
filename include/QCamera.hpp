#pragma once
#include <QEntity.hpp>

class QCamera: public QEntity {
public:
	QCamera();
	void* getMatrix();
	void update();
};
