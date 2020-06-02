#pragma once
#include "../Utilities/utilities.h"
#include "stdafx.h"
#include "Shaders.h"

class Model
{
public:
	GLuint m_VBO, m_IBO;
	unsigned int m_indicesCount, m_verticesCount;
	Model();
	~Model();
	void initModel(char* filename);
	void draw(Shaders shader);
};

