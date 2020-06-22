#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"

Camera::Camera(): Object3D() {}
Camera::~Camera() {}

Matrix Camera::GetViewMatrix() {
	Matrix view, translate, rotz, rotx, roty;

	view.SetIdentity();

	translate.SetIdentity();
	translate.SetTranslation(this->transform.position * -1);
	
	rotz.SetIdentity();
	rotz.SetRotationZ(-1 * this->transform.rotation.z);
	rotx.SetIdentity();
	rotx.SetRotationX(-1 * this->transform.rotation.x);
	roty.SetIdentity();
	roty.SetRotationY(-1 * this->transform.rotation.y);



	view = translate * roty * rotx * rotz;
	return view;
}

Matrix Camera::GetProjectionMatrix() {
	float fovY = 1.0;
	float aspectRatio = (float)Globals::screenWidth / (float)Globals::screenHeight;

	float nearPlane = 0.001f;
	float farPlane = 500.0f;

	Matrix proj;
	proj.SetIdentity();
	proj.SetPerspective(fovY, aspectRatio, nearPlane, farPlane);

	return proj;
}

void Camera::drawSkybox() 
{
	glDepthMask(GL_FALSE);
	glUseProgram(this->skybox->GetShader()->GetProgram());

	Matrix world;
	world.SetIdentity();
	world = this->skybox->GetWorldMatrix() * this->GetViewMatrix() * this->GetProjectionMatrix();

	if (this->skybox->GetShader()->GetUniforms().wvp_matrix != -1) {
		glUniformMatrix4fv(this->skybox->GetShader()->GetUniforms().wvp_matrix, 1, GL_FALSE, world.m[0]);
	}

	glBindBuffer(GL_ARRAY_BUFFER, this->skybox->GetModel()->m_VBO);
	if( this->skybox->GetShader()->GetAttributes().position != -1 )
	{	
		glEnableVertexAttribArray( this->skybox->GetShader()->GetAttributes().position );
		glVertexAttribPointer( this->skybox->GetShader()->GetAttributes().position, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex), 0);
	}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->skybox->GetTexture()->textureID);
	glUniform1i(this->skybox->GetShader()->GetUniforms().texture, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->skybox->GetModel()->m_IBO);
	glDrawElements(GL_TRIANGLES, this->skybox->GetModel()->m_indicesCount, GL_UNSIGNED_INT, 0);
	
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDepthMask(GL_TRUE);
}

void Camera::draw(Object3D* object) 
{
	glUseProgram(object->GetShader()->GetProgram());

	Matrix world;
	world.SetIdentity();
	world = object->GetWorldMatrix() * this->GetViewMatrix() * this->GetProjectionMatrix();
	//world = object->GetWorldMatrix();

	if (object->GetShader()->GetUniforms().wvp_matrix != -1) {
		glUniformMatrix4fv(object->GetShader()->GetUniforms().wvp_matrix, 1, GL_FALSE, world.m[0]);
	}

	if (object->GetShader()->GetUniforms().texture != -1) {
		glUniform1i(object->GetShader()->GetUniforms().texture, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, object->GetTexture()->textureID);
	}

	if (object->GetShader()->GetUniforms().skybox != -1) {
		glUniform1i(object->GetShader()->GetUniforms().skybox, 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, this->skybox->GetTexture()->textureID);
	}

	glBindBuffer(GL_ARRAY_BUFFER, object->GetModel()->m_VBO);
	if( object->GetShader()->GetAttributes().position != -1 )
	{	
		glEnableVertexAttribArray( object->GetShader()->GetAttributes().position );
		glVertexAttribPointer( object->GetShader()->GetAttributes().position, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex), 0);
	}

	if (object->GetShader()->GetAttributes().textureCoord != -1)
	{
		glEnableVertexAttribArray(object->GetShader()->GetAttributes().textureCoord);
		glVertexAttribPointer(object->GetShader()->GetAttributes().textureCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3));
	}

	if (object->GetShader()->GetAttributes().normal != -1)
	{
		glEnableVertexAttribArray(object->GetShader()->GetAttributes().normal);
		glVertexAttribPointer(object->GetShader()->GetAttributes().normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3) + sizeof(Vector2));
	}

	if (object->GetShader()->GetUniforms().model != -1)
	{	
		Matrix World4 = object->GetWorldMatrix();
		glUniformMatrix4fv(object->GetShader()->GetUniforms().model, 1, GL_FALSE, World4.m[0]);
	}

	if (object->GetShader()->GetUniforms().camera != -1) {
		glUniform3f(object->GetShader()->GetUniforms().camera, this->transform.position.x, this->transform.position.y, this->transform.position.z);
	}

	if (object->GetShader()->GetUniforms().color != -1) {
		glUniform3f(object->GetShader()->GetUniforms().color, object->color.x, object->color.y, object->color.z);
	}

	if (object->GetShader()->GetUniforms().lightpos != -1) {
		glUniform3f(object->GetShader()->GetUniforms().lightpos, this->light->transform.position.x, this->light->transform.position.y, this->light->transform.position.z);
	}

	if (object->GetShader()->GetUniforms().lightcolor != -1) {
		glUniform3f(object->GetShader()->GetUniforms().lightcolor, this->light->color.x, this->light->color.y, this->light->color.z);
	}

	if (object->GetShader()->GetUniforms().ambientcolor != -1) {
		glUniform3f(object->GetShader()->GetUniforms().ambientcolor, this->ambientColor.x, this->ambientColor.y, this->ambientColor.z);
	}

	glBindBuffer(GL_ARRAY_BUFFER, object->GetModel()->m_VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->GetModel()->m_IBO);
	glDrawElements(GL_TRIANGLES, object->GetModel()->m_indicesCount, GL_UNSIGNED_INT, 0);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Camera::update(float deltaTime) {
	Vector3 camdir = Vector3(0, 0, 0);
	Vector3 camrot = Vector3(0, 0, 0);

	if (GetAsyncKeyState('W')) {
		camdir.z = -1;
	} else if (GetAsyncKeyState('S')) {
		camdir.z = 1;
	}

	if (GetAsyncKeyState('A')) {
		camdir.x = -1;
	} else if (GetAsyncKeyState('D')) {
		camdir.x = 1;
	}

	if (GetAsyncKeyState(37)) {
		camrot.y = 1;
	} else if (GetAsyncKeyState(39)) {
		camrot.y = -1;
	}

	if (GetAsyncKeyState(38)) {
		camrot.x = 1;
	} else if (GetAsyncKeyState(40)) {
		camrot.x = -1;
	}
	Vector4 dir;

	dir.x = camdir.x * deltaTime;
	dir.y = camdir.y * deltaTime;
	dir.z = camdir.z * deltaTime;

	dir = dir * this->GetWorldMatrix();

	this->transform.position += Vector3(dir.x, dir.y, dir.z) * 3;
	this->transform.rotation += Vector3(camrot.x * deltaTime, camrot.y * deltaTime, camrot.z * deltaTime);

	this->skybox->transform.position = this->transform.position;
}

