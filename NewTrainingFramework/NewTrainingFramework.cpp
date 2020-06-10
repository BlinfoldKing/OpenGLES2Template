// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>

Shaders			myShaders;
Object3D*		woman1;
Model*			model2;
Rect*			rect;

int Init( ESContext *esContext )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glEnable(GL_DEPTH_TEST);
	
	char* woman1model = "../Resources/Models/Woman1.nfg";
	char* woman1text = "../Resources/Textures/Woman1.tga";

	char* vertexpath = "../Resources/Shaders/ModelShaderVS.vs";
	char* fragmentpath = "../Resources/Shaders/ModelShaderFS.fs";

	woman1 = new Object3D();
	woman1->SetModel(woman1model);
	woman1->SetTexture(woman1text);
	woman1->SetShader(vertexpath, fragmentpath);
	woman1->transform.position.y = -1;


//	model2 = new Model(Vector3(1, -1, 0));
//	model2->initModel(path2);
//	model2->texture.InitTexture("../Resources/Textures/Woman2.tga");
//	model2->shader.Init("../Resources/Shaders/ModelShaderVS.vs", "../Resources/Shaders/ModelShaderFS.fs");


	Vector3 positions[4] = {
		Vector3(-0.5, 0.5, 0.0),
		Vector3(0.5, 0.5, 0.0),
		Vector3(0.5, -0.5, 0.0),
		Vector3(-0.5, -0.5, 0.0)
	};
	
	rect = new Rect();
	rect->initVertices(positions);

	//creation of shaders and program 
	myShaders.Init( "../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs" );
	return 0;
}

void Draw( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram( myShaders.GetProgram() );

	woman1->draw();
	//rect->draw(myShaders);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	eglSwapBuffers( esContext->eglDisplay, esContext->eglSurface );
}

void Update( ESContext *esContext, float deltaTime )
{

}

void Key( ESContext *esContext, unsigned char key, bool bIsPressed )
{

}

void CleanUp()
{
	//Cleaning up the buffers
	delete woman1;
	delete rect;
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

