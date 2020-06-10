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

	glBindBuffer(GL_ARRAY_BUFFER, object->GetModel()->m_VBO);
	if( object->GetShader()->GetAttributes().position != -1 )
	{	
		glEnableVertexAttribArray( object->GetShader()->GetAttributes().position );
		glVertexAttribPointer( object->GetShader()->GetAttributes().position, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex), 0);
	}

	glBindTexture(GL_TEXTURE_2D, object->GetTexture()->textureID);
	glUniform1i(object->GetShader()->GetUniforms().texture, 0);
	if (object->GetShader()->GetAttributes().textureCoord != -1)
	{
		glEnableVertexAttribArray(object->GetShader()->GetAttributes().textureCoord);
		glVertexAttribPointer(object->GetShader()->GetAttributes().textureCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3));
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->GetModel()->m_IBO);
	glDrawElements(GL_TRIANGLES, object->GetModel()->m_indicesCount, GL_UNSIGNED_INT, 0);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}