#pragma once
#include "stdafx.h"
#include "Object3D.h"

class Camera: public Object3D
{
public:
	Camera();
	virtual ~Camera();
	Matrix GetViewMatrix();
	Matrix GetProjectionMatrix();

	void draw(Object3D* object);
};

