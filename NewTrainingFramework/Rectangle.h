#pragma once
#include "stdafx.h";
#include "Shaders.h";
#include "../Utilities/utilities.h"

class Rect
{
public:
	Vertex vertices[4];
	GLuint m_VBO, m_IBO;
	Rect();
	~Rect();
	void initVertices(Vector3 positions[4]);
	void draw(Shaders shader);
};

