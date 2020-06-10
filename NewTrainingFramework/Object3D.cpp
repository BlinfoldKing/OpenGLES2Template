#include "stdafx.h"
#include "Object3D.h"

Object3D::Object3D() {
	this->model = new Model();
	this->texture = new Texture();
	this->shader = new Shaders();
	this->transform.scale = Vector3(1, 1, 1);
	this->transform.position = Vector3(0, 0, 0);
	this->transform.rotation = Vector3(0, 0, 0);
}

Object3D::~Object3D() {
	delete this->model;
	delete this->texture;
	delete this->shader;
}

void Object3D::SetModel(char* path) {
	this->model->init(path);
}

void Object3D::SetTexture(char* path) {
	this->texture->init(path);
}

void Object3D::SetShader(char* vertexpath, char* fragmentpath) {
	this->shader->Init(vertexpath, fragmentpath);
}

Matrix Object3D::GetWorldMatrix() {
	Matrix world, scale, rotz, rotx, roty, translate;

	world.SetIdentity();
	
	scale.SetIdentity();
	scale.SetScale(this->transform.scale);
	
	translate.SetIdentity();
	translate.SetTranslation(this->transform.position);
	
	rotz.SetIdentity();
	rotz.SetRotationZ(this->transform.rotation.z);
	rotx.SetIdentity();
	rotx.SetRotationX(this->transform.rotation.x);
	roty.SetIdentity();
	roty.SetRotationY(this->transform.rotation.y);

	world = scale * rotz * rotx * roty * translate;
	return world;
}

void Object3D::draw() 
{
	glUseProgram(this->shader->GetProgram());

	Matrix world = this->GetWorldMatrix();

	if (this->shader->GetUniforms().mvp_matrix != -1) {
		glUniformMatrix4fv(this->shader->GetUniforms().mvp_matrix, 1, GL_FALSE, world.m[0]);
	}

	glBindBuffer(GL_ARRAY_BUFFER, this->model->m_VBO);
	if( this->shader->GetAttributes().position != -1 )
	{	
		glEnableVertexAttribArray( this->shader->GetAttributes().position );
		glVertexAttribPointer( this->shader->GetAttributes().position, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex), 0);
	}

	glBindTexture(GL_TEXTURE_2D, this->texture->textureID);
	glUniform1i(this->shader->GetUniforms().texture, 0);
	if (this->shader->GetAttributes().textureCoord != -1)
	{
		glEnableVertexAttribArray(this->shader->GetAttributes().textureCoord);
		glVertexAttribPointer(this->shader->GetAttributes().textureCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3));
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->model->m_IBO);
	glDrawElements(GL_TRIANGLES, this->model->m_indicesCount, GL_UNSIGNED_INT, 0);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
