#pragma once

#define CHUNK_WIDTH 16
#define CHUNK_LENGTH 16
#define CHUNK_HEIGHT 256

class QChunkMesh;
class QChunk {
	unsigned short blocksData[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_LENGTH];
	QChunkMesh* mesh;

protected:
public:
	QChunk();
	void initBlocksData(unsigned int x, unsigned int z);
	void updateMesh();
	QChunkMesh* getMesh();

	inline unsigned short data(int x, int y, int z) {
		return blocksData[x][y][z];
	}
};
