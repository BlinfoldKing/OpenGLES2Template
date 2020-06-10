#pragma once
#include "../Utilities/utilities.h"

class Texture
{
public:
	GLuint textureID;
	char* data = '\0';
	int width, height, bpp;
	Texture();
	~Texture();
	void init(char* filename);
};

