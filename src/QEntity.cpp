#include <QEntity.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <string.h>

static glm::mat4x4 __matrix_default__ = glm::mat4x4(1.0f);
static glm::mat4x4 __matrix_cache__ = glm::mat4x4(1.0f);
static glm::vec4 __vector_cache__ = glm::vec4(0.0f);

QEntity::QEntity() : pitch(0.0f), yaw(0.0f), position(0.0f, 0.0f, 0.0f) {
	matrix = (void*) new glm::mat4x4(1.0f);
}

void QEntity::recalcMatrix() {
	glm::mat4x4* mat = (glm::mat4x4*) matrix;

	if (this->pitch >= 90.0f) 
		this->pitch = 90.0f;
		
	if (this->pitch <= -90.0f) 
		this->pitch = -90.0f;
	
	// static float clamp = 180.0f;
	// this->yaw = glm::modf(180.0f, this->yaw);
	(*mat) = __matrix_default__;
	(*mat) = glm::translate((*mat), glm::vec3(position.x, position.y, position.z));
	(*mat) = glm::rotate((*mat), glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	(*mat) = glm::rotate((*mat), glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	dirty = false;
}

void* QEntity::getMatrix() {
	if (dirty) {
		recalcMatrix();
	}
	return matrix;
}

float QEntity::getPitch() {
	return pitch;
}

float QEntity::getYaw() {
	return yaw;
}

void QEntity::turn(float pitch, float yaw) {
	this->pitch += pitch;
	this->yaw += yaw;
	dirty = true;
}

void QEntity::setRotation(float pitch, float yaw) {
	this->pitch = pitch;
	this->yaw = yaw;
	dirty = true;
}

QVector3 QEntity::getPosition() {
	return position;
}

void QEntity::setPosition(QVector3 pos) {
	position = pos;
	dirty = true;
}

void QEntity::move(QVector3 pos, bool allowPitch) {
	__matrix_cache__ = __matrix_default__;
	
	if(allowPitch) {
		__matrix_cache__ = glm::rotate(__matrix_cache__, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	__matrix_cache__ = glm::rotate(__matrix_cache__, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));

	__vector_cache__.x = pos.x;
	__vector_cache__.y = pos.y;
	__vector_cache__.z = pos.z;
	__vector_cache__.w = 0.0f;

	__vector_cache__ =  __vector_cache__ * __matrix_cache__;

	pos.x = __vector_cache__.x;
	pos.y = __vector_cache__.y;
	pos.z = __vector_cache__.z;
	
	position.x += pos.x;
	position.y += pos.y;
	position.z += pos.z;

	dirty = true;
}