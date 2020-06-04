#pragma once
#include "../Utilities/utilities.h"
#include "stdafx.h"
#include "Shaders.h"
#include "Texture.h"

class Model
{
public:
	GLuint m_VBO, m_IBO;
	unsigned int m_indicesCount, m_verticesCount;
	Shaders shader;
	Texture texture;
	Model();
	~Model();
	void initModel(char* filename);
	void draw();
};

