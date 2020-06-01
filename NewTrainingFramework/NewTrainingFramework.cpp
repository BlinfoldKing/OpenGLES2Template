// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>


Shaders		myShaders;
Vertex		rect[4];
GLuint		vboId;
GLuint		iboId;

void InitRect()
{
	//rect data
	rect[0].pos = Vector3(-0.5, 0.5, 0.0);
	rect[1].pos = Vector3(0.5, 0.5, 0.0);
	rect[2].pos = Vector3(0.5, -0.5, 0.0);
	rect[3].pos = Vector3(-0.5, -0.5, 0.0);


	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	int indices[6] = { 0, 1, 2, 3, 2, 0 };
	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rect), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int Init( ESContext *esContext )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	char* path = "c:\\\\Users\\ganes\\project\\OpenGLES2Template\\Resources\\Models\\Woman1.nfg";
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		printf(path);
		printf("Impossible to open the file !\n");
		return false;
	}
	else {
		int NrVertices;
		fscanf_s(file, "NrVertices: %d", &NrVertices);
		Vertex* verticesData = new Vertex[NrVertices];

		printf("%d\n", NrVertices);
		char* format = " %*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm: [%f, %f, %f] ; tgt: [%f, %f, %f] ; uv: [%f, %f];\n";
		for (int i = 0; i < NrVertices; i++) {
			Vertex v;
			fscanf_s(file, format,
				&v.pos.x, &v.pos.y, &v.pos.z,
				&v.norm.x, &v.norm.y, &v.norm.z,
				&v.binorm.x, &v.binorm.y, &v.binorm.z,
				&v.tgt.x, &v.tgt.y, &v.tgt.z,
				&v.uv.x, &v.uv.y
			);
			verticesData[i] = v;
		}

		printf("%f %f %f", verticesData[0].pos.x, verticesData[1].pos.x, verticesData[2].pos.x);
		glGenBuffers(1, &vboId);
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		int NrIndices;
		fscanf_s(file, "NrIndices: %d", &NrIndices);
		printf("%d\n", NrIndices);
		int* indicesdData = new int[NrIndices];
		format = "   %*d.    %d,    %d,    %d";
		for (int i = 0; i < NrIndices; i += 3) {
			fscanf_s(file, format,
				&indicesdData[i],
				&indicesdData[i + 1],
				&indicesdData[i + 2]
			);
		}

		glGenBuffers(1, &iboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(verticesData), indicesdData, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	InitRect();

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
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (char*) 0 + sizeof(Vector3));
	
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

