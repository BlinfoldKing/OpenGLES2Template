#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h"

class SkyBox: public Object3D
{
public:
	SkyBox();
	virtual ~SkyBox();
	void LoadSkyboxTextures(char* paths[6]);
};

