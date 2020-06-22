#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	struct Attributes
	{
		GLint position;
		GLint normal;
		GLint textureCoord;
	};

	struct Uniforms
	{
		GLint texture;
		GLint skybox;
		GLint wvp_matrix;
		GLint model;
		GLint camera;
		GLint color;
		GLint lightpos;
		GLint lightcolor;
		GLint ambientcolor;
	};

private:
	GLuint		m_program;
	GLuint		m_vertexShader; 
	GLuint		m_fragmentShader;

	Attributes	m_attributes;
	Uniforms	m_uniforms;

public:
	int			Init( char * fileVertexShader, char * fileFragmentShader );
	
	// Getters
	GLuint		GetProgram() const;
	Attributes	GetAttributes() const;
	Uniforms	GetUniforms() const;
	
	~Shaders();
};