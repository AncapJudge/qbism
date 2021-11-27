#include <App.hpp>

#include <iostream>
#include <QWindow.hpp>
#include <QColor.hpp>
#include <QEvent.hpp>
#include <QChunkMesh.hpp>
#include <QChunk.hpp>
#include <QCamera.hpp>
#include <QShaderProgram.hpp>
#include <QTexture.hpp>
#include <QFile.hpp>

int App::run() {
	QApplication::run();
	QWindow* window = QWindow::getInstance();
	
	if (!window->open(1280, 720, "QBism")) {
		return -1;
	}
	QCamera* camera = new QCamera();
	QChunk* chunks[4][4];
	
	QShaderProgram* shaderProgram = QShaderProgram::load("./assets/shader.glslv", "./assets/shader.glslf");
	QTexture* texture = QTexture::load("./assets/grass.png");
	
	int bl = 69;

	for (int x = 0; x < 4; x++) {
		for (int z = 0; z < 4; z++) {
			chunks[x][z] = new QChunk(x, z);
			chunks[x][z]->initBlocksData();
			chunks[x][z]->updateMesh();
			QChunkMesh* chunkMesh = chunks[x][z]->getMesh();
			chunkMesh->setShaderProgram(shaderProgram);
			chunkMesh->setTexture(texture);
		}
	}
	
	
	
	QEvent* ev_in = QEvent::getInstance();
	ev_in->lockMouse();

	camera->setPosition(QVector3(8, 70, 2));
	camera->setRotation(0.0f, 180.0f);
	do {
		
		if (ev_in->mouseHit(0)) {
			ev_in->lockMouse();
		}

		if (ev_in->mouseHit(1)) {
			ev_in->unlockMouse();
		}

		if (ev_in->isMouseLocked()) {
			int deltaX, deltaY;
			ev_in->getMouseDelta(&deltaX, &deltaY);
			camera->turn((float)deltaY / 10, (float)deltaX / 10);
		}
		
		if(ev_in->keyHit(KEY::F)) {
			if (bl >= 0) 
				chunks[0][0]->setBlock(1, bl--, 1, 0);
		}
		
		const bool ALLOW_VERT = false;
		if(ev_in->keyDown(KEY::W)) {
			camera->move(QVector3(
				0.0f,
				0.0f,
				-0.1f
			), ALLOW_VERT);
		}
		
		if(ev_in->keyDown(KEY::S)) {
			camera->move(QVector3(
				0.0f,
				0.0f,
				0.1f
			), ALLOW_VERT);
		}
		if(ev_in->keyDown(KEY::A)) {
			camera->move(QVector3(
				-0.1f,
				0.0f,
				0.0f
			), ALLOW_VERT);
		}
		
		if(ev_in->keyDown(KEY::D)) {
			camera->move(QVector3(
				0.1f,
				0.0f,
				0.0f
			), ALLOW_VERT);
		}
		
		if(ev_in->keyDown(KEY::SPACE)) {
			camera->move(QVector3(
				0.0f,
				0.1f,
				0.0f
			), ALLOW_VERT);
		}
		
		if(ev_in->keyDown(KEY::LEFT_SHIFT)) {
			camera->move(QVector3(
				0.0f,
				-0.1f,
				0.0f
			), ALLOW_VERT);
		}

		shaderProgram->uniformMatrix("matrix", camera->getMatrix());
		window->clear();
		ev_in->pollEvents();
		for (int x = 0; x < 4; x++) {
			for (int z = 0; z < 4; z++) {
				chunks[x][z]->getMesh()->draw();
			}
		}
		window->swapBuffers();
	} while(window->isOpen());

	window->termitate();
    return 0;
}