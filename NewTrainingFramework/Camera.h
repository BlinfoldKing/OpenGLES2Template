#pragma once
#include "stdafx.h"
#include "Object3D.h"
#include "SkyBox.h"

class Camera: public Object3D
{
public:
	Camera();
	virtual ~Camera();
	Matrix GetViewMatrix();
	Matrix GetProjectionMatrix();
	void drawSkybox();
	void draw(Object3D* object);
	void update(float deltaTime);
	SkyBox* skybox;
};

