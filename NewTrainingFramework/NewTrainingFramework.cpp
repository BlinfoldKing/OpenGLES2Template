// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>

Shaders			myShaders;
Camera*			camera;
Object3D*		woman1;
Object3D*		woman2;
Rect*			rect;
int scene = 1;

int Init( ESContext *esContext )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glEnable(GL_DEPTH_TEST);
	
	char* woman1model = "../Resources/Models/Woman1.nfg";
	char* woman1text = "../Resources/Textures/Woman1.tga";
	
	char* woman2model = "../Resources/Models/Woman2.nfg";
	char* woman2text = "../Resources/Textures/Woman2.tga";

	char* vertexpath = "../Resources/Shaders/ModelShaderVS.vs";
	char* fragmentpath = "../Resources/Shaders/ModelShaderFS.fs";
	
	char* debugvertexpath = "../Resources/Shaders/DebugShader.vs";
	char* debugfragmentpath = "../Resources/Shaders/DebugShader.fs";


	woman1 = new Object3D();
	woman1->SetModel(woman1model);
	woman1->SetTexture(woman1text);
	woman1->SetShader(vertexpath, fragmentpath);
	woman1->transform.position.x = -0.5;
	woman1->transform.position.y = -0.5;
	woman1->transform.position.z = -0.5;
	woman1->transform.scale = Vector3(0.6, 0.6, 0.6);

	woman2 = new Object3D();
	woman2->SetModel(woman2model);
	woman2->SetTexture(woman2text);
	woman2->SetShader(vertexpath, fragmentpath);
	woman2->transform.position.x = 0.5;
	woman2->transform.position.y = -0.5;
	woman2->transform.position.z = 0.5;
	woman2->transform.scale = Vector3(0.5, 0.5, 0.5);

	camera = new Camera();
	camera->skybox = new SkyBox();
	
	char* skyboxpaths[6] = {
		"../Resources/Textures/SkyBox_Right.tga",
		"../Resources/Textures/SkyBox_Left.tga",
		"../Resources/Textures/SkyBox_Top.tga",
		"../Resources/Textures/SkyBox_Bottom.tga",
		"../Resources/Textures/SkyBox_Front.tga",
		"../Resources/Textures/SkyBox_Back.tga",
	};
	char* cubeVertex = "../Resources/Shaders/CubeShader.vs";
	char* cubeFragment = "../Resources/Shaders/CubeShader.fs";
	char* skyboxModel = "../Resources/Models/SkyBox.nfg";

	camera->skybox->LoadSkyboxTextures(skyboxpaths);
	camera->skybox->SetModel(skyboxModel);
	camera->skybox->SetShader(cubeVertex, cubeFragment);

//	Vector3 positions[4] = {
//		Vector3(-0.5, 0.5, 0.0),
//		Vector3(0.5, 0.5, 0.0),
//		Vector3(0.5, -0.5, 0.0),
//		Vector3(-0.5, -0.5, 0.0)
//	};
	
	//rect = new Rect();
	//rect->initVertices(positions);


	//creation of shaders and program 
//	myShaders.Init( "../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs" );
	return 0;
}

void Draw( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera->drawSkybox();

	switch (scene)
	{
	case 1:
		camera->draw(woman1);
		camera->draw(woman2);
		break;
	default:
		break;
	}
//rect->draw(myShaders);

	eglSwapBuffers( esContext->eglDisplay, esContext->eglSurface );
}

void Update( ESContext *esContext, float deltaTime )
{
	woman1->transform.rotation.y += deltaTime;
	woman2->transform.rotation.z += deltaTime;
	camera->update(deltaTime);
}

void Key( ESContext *esContext, unsigned char key, bool bIsPressed )
{
	if (bIsPressed) {
		if (key >= '1' && key <= '9') {
			scene = (int)key - '0';
		}
	}
}

void CleanUp()
{
	//Cleaning up the buffers
	delete woman1;
	delete woman2;
	delete camera;
}

int _tmain( int argc, _TCHAR* argv[] )
{
	ESContext esContext;

	esInitContext( &esContext );

	esCreateWindow( &esContext, "Hello OpenGLES 2", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH );

	if( Init( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc( &esContext, Draw );
	esRegisterUpdateFunc( &esContext, Update );
	esRegisterKeyFunc( &esContext, Key );

	esMainLoop( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf( "Press any key...\n" );
	_getch();

	return 0;
}

