#include "stdafx.h"
#include "SkyBox.h"

SkyBox::SkyBox(): Object3D() {
}

SkyBox::~SkyBox() {
}

void SkyBox::LoadSkyboxTextures(char* paths[6]) {
	this->texture->loadSkybox(paths);
}

