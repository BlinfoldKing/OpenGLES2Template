// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include <iostream>


Shaders		myShaders;
Vertex		verticesData[6];
GLuint		vboId;

int Init( ESContext *esContext )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	//triangle data
	verticesData[0].pos = Vector3(  -0.5,  0.5,  0.0 );
	verticesData[1].pos = Vector3( 0.5, 0.5,  0.0 );
	verticesData[2].pos = Vector3(  0.5, -0.5,  0.0 );
	verticesData[3].pos = Vector3(  -0.5,  0.5,  0.0 );
	verticesData[4].pos = Vector3( -0.5, -0.5,  0.0 );
	verticesData[5].pos = Vector3(  0.5, -0.5,  0.0 );


	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//creation of shaders and program 
	myShaders.Init( "../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs" );
	return 0;
}

void Draw( ESContext *esContext )
{
	glClear( GL_COLOR_BUFFER_BIT );

	glUseProgram( myShaders.GetProgram() );

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	if( myShaders.GetAttributes().position != -1 )
	{	
		glEnableVertexAttribArray( myShaders.GetAttributes().position );
		glVertexAttribPointer( myShaders.GetAttributes().position, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex), 0);
		//glDrawArrays( GL_TRIANGLES, 0, 3 );
		//glDrawArrays( GL_TRIANGLES, 0, 3 );
	}
	glDrawArrays( GL_TRIANGLES, 0, 3 );
	glDrawArrays( GL_TRIANGLES, 3, 3 );
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
	
	//glDeleteBuffers( 1, &vboId );
	//glDeleteBuffers( 1, &iboId );
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
