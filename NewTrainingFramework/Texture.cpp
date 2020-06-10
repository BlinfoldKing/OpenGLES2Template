#include "stdafx.h"
#include "Texture.h"

Texture::Texture()
{
	// Generate the texture
	glGenTextures(1, &this->textureID);
}

Texture::~Texture()
{
	if ((this->data != NULL) && (this->data[0] != '\0')) delete this->data;
}

void Texture::init(char* filename)
{
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
}