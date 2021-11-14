#pragma once

class QTexture {
protected:
	unsigned int id;
	QTexture();
public:
	~QTexture();
	static bool load(const char* filename);
	unsigned int getId();
};
