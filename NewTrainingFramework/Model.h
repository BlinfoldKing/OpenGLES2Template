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
	
	Model();
	~Model();
	
	void init(char* filename);
};

