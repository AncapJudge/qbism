#include <QCamera.hpp>
#include <QEvent.hpp>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
QCamera::QCamera() : QEntity() {}

static glm::mat4x4 __matrix_default__ = glm::mat4x4(1.0f);
static glm::mat4 __matrix_cache__ = glm::mat4(0.0f);
static glm::vec4 __vector_cache1__ = glm::vec4(0.0f);
static glm::vec4 __vector_cache2__ = glm::vec4(0.0f);
static glm::vec4 __vector_cache3__ = glm::vec4(0.0f);
static glm::vec4 __vector_cache4__ = glm::vec4(0.0f);

static glm::vec4 __zero_vector__ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

static glm::vec4 __front_vector__ = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
static glm::vec4 __up_vector__ = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
static glm::vec4 __right_vector__ = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);

void* QCamera::getMatrix() {
	glm::mat4* mat = (glm::mat4*) QEntity::getMatrix();
	__matrix_cache__ = __matrix_default__;
	__matrix_cache__ = glm::rotate(__matrix_cache__, glm::radians(getPitch()), glm::vec3(1.0f, 0.0f, 0.0f));
	__matrix_cache__ = glm::rotate(__matrix_cache__, glm::radians(getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));

	__vector_cache1__ = __front_vector__ * __matrix_cache__;
	__vector_cache2__ = __up_vector__ * __matrix_cache__;
	
	__vector_cache4__ = (*mat) * __zero_vector__;

	
	__vector_cache1__ += __vector_cache4__;
	
	__vector_cache1__.w = 1.0f;
	__vector_cache2__.w = 1.0f;
	
	__matrix_cache__ = glm::perspective(
		glm::radians(90.0f),
		16.0f / 9.0f,
		0.1f,
		1000.0f
	);

	__matrix_cache__ *= glm::lookAt(
		glm::vec3(__vector_cache4__),
		glm::vec3(__vector_cache1__),
		glm::vec3(__vector_cache2__)
	);

	return (void*) &__matrix_cache__;
}

void QCamera::update() {
	QEvent* ev = QEvent::getInstance();

	int deltaX, deltaY;
	ev->getMouseDelta(&deltaX, &deltaY);
	turn((float)deltaY / 10, (float)deltaX / 10);

	
	if (ev->mouseHit(2)) {
		QVector3 p = getPosition();
		std::cout << p.x << " " << p.y << " " << p.z << "\n";
	}
	const bool ALLOW_VERT = true;
	if(ev->keyDown(25)) {
		move(QVector3(
			0.0f,
			0.0f,
			-0.1f
		), ALLOW_VERT);
	}
	
	if(ev->keyDown(39)) {
		move(QVector3(
			0.0f,
			0.0f,
			0.1f
		), ALLOW_VERT);
	}
	if(ev->keyDown(38)) {
		move(QVector3(
			-0.1f,
			0.0f,
			0.0f
		), ALLOW_VERT);
	}
	
	if(ev->keyDown(40)) {
		move(QVector3(
			0.1f,
			0.0f,
			0.0f
		), ALLOW_VERT);
	}
}