#pragma once
#include "../Utilities/utilities.h"

class Texture
{
public:
	GLuint textureID;
	char* data;
	int width, height, bpp;
	Texture();
	~Texture();
	void InitTexture(char* filename);
};

