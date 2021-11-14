#pragma once

#include <glm/glm.hpp>
#include <QVector3.hpp>

class QEntity {
	bool dirty;
	void* matrix;

	float pitch;
	float yaw;

	QVector3 position;
	void recalcMatrix();

public:
	QEntity();
	float getPitch();
	float getYaw();
	void setRotation(float pitch, float yaw);
	void turn(float pitch, float yaw);

	QVector3 getPosition();
	void setPosition(QVector3 pos);
	void move(QVector3 pos, bool allowPitch = true);
	
	void* getMatrix();
};
