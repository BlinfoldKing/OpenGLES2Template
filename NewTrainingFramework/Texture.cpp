#include "stdafx.h"
#include "Texture.h"

Texture::Texture()
{
	// Generate the texture
}

Texture::~Texture()
{
	if ((this->data != NULL) && (this->data[0] != '\0')) delete this->data;
}

void Texture::load(char* filename)
{
	glGenTextures(1, &this->textureID);
	// Bind and load Texture data
	glBindTexture(GL_TEXTURE_2D, textureID);
	this->data = LoadTGA(filename, &width, &height, &bpp);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_RGB, GL_UNSIGNED_BYTE, this->data);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::loadSkybox(char* paths[6]) {
	glGenTextures(1, &this->textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);

	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	for (int i = 0; i < 6; i++) {
		int width, height, bpp;
		char* cubePixel = LoadTGA(paths[i], &width, &height, &bpp);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, cubePixel);
		delete cubePixel;
	}
	

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}