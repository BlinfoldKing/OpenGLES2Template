#pragma once

#include "stdafx.h"

struct Transform {
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
};

class Object3D
{
protected:
    Texture* texture;
    Model*   model;
    Shaders* shader;
 
public:
	Vector3 color;
    Transform transform;
    Object3D();
    virtual ~Object3D();

    void SetModel(char* path);
    void SetTexture(char* path);
    void SetShader(char* vertexpath, char* fragmentpath);
 
    Model* GetModel();
    Texture* GetTexture();
    Shaders* GetShader();
    
    Matrix GetWorldMatrix();
};

