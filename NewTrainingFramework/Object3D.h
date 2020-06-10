#pragma once

#include "stdafx.h"

struct Transform {
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
};

class Object3D
{
private:
    Texture* texture;
    Model*   model;
    Shaders* shader;
 
public:
   
    Transform transform;
    Object3D();
    ~Object3D();

    void SetModel(char* path);
    void SetTexture(char* path);
    void SetShader(char* vertexpath, char* fragmentpath);
     
    void draw();
    
    Matrix GetWorldMatrix();
};
