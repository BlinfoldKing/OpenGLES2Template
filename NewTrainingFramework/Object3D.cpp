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
	if (this->model) delete this->model;
	if (this->texture) delete this->texture;
	if (this->shader) delete this->shader;
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

Model* Object3D::GetModel() {
	return this->model;
}

Texture* Object3D::GetTexture() {
	return this->texture;
}

Shaders* Object3D::GetShader() {
	return this->shader;
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
	printf("%f\n", world);
	return world;
}


