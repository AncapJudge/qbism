#include <QChunk.hpp>
#include <QChunkMesh.hpp>

QChunk::QChunk(int x, int z): x(x), z(z) {
	mesh = new QChunkMesh();
}

void QChunk::initBlocksData() {
	for (int x = 0; x < CHUNK_WIDTH; x++) {
		for (int y = 0; y < CHUNK_HEIGHT; y++) {
			for (int z = 0; z < CHUNK_LENGTH; z++) {
				if (y < 67) {
					blocksData[x][y][z] = 1;
				}
				else {
					blocksData[x][y][z] = 0;
				}
			}
		}
	}
}

void QChunk::updateMesh() {
	mesh->updateMesh(this);
}

QChunkMesh* QChunk::getMesh() {
	return mesh;
}

void QChunk::setBlock(unsigned int x, unsigned int y, unsigned int z, unsigned int id) {
	blocksData[x][y][z] = id;
	updateMesh();
}
