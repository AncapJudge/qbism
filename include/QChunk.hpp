#pragma once

#define CHUNK_WIDTH 16
#define CHUNK_LENGTH 16
#define CHUNK_HEIGHT 256

class QChunkMesh;
class QChunk {
	unsigned short blocksData[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_LENGTH];
	int x, z;
	QChunkMesh* mesh;
protected:
public:
	QChunk(int x, int z);
	void initBlocksData();
	void updateMesh();
	QChunkMesh* getMesh();

	void setBlock(unsigned int x, unsigned int y, unsigned int z, unsigned int id);

	inline unsigned short data(int x, int y, int z) {
		return blocksData[x][y][z];
	}
	inline int getXPosition() { return x; }
	inline int getZPosition() { return z; }
};
