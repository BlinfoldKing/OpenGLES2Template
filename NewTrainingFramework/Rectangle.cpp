#include "stdafx.h"
#include "Rectangle.h"
#include "Shaders.h"

Rect::Rect()
{
	glGenBuffers(1, &this->m_VBO);
	glGenBuffers(1, &this->m_IBO);
}

Rect::~Rect()
{
	glDeleteBuffers(1, &this->m_VBO);
	glDeleteBuffers(1, &this->m_IBO);
}

void Rect::initVertices(Vector3 positions[4]) {
	//rect data
	this->vertices[0].pos = positions[0];
	this->vertices[1].pos = positions[1];
	this->vertices[2].pos = positions[2];
	this->vertices[3].pos = positions[3];
	

	glGenBuffers(1, &this->m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER,this->m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	int indices[6] = { 0, 1, 2, 3, 2, 0 };
	glGenBuffers(1, &this->m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Rect::draw(Shaders shader) {
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
	if( shader.GetAttributes().position != -1 )
	{	
		glEnableVertexAttribArray( shader.GetAttributes().position );
		glVertexAttribPointer( shader.GetAttributes().position, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex), 0);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_IBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*) 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
