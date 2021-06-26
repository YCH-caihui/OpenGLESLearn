#pragma once

#include <GLES3/gl3.h>

typedef GLint attribute;
typedef GLint uniform;


class GLProgram
{
public:
	GLProgram(const GLchar* vs, const GLchar* fs);
	void use();
	attribute getAttribLocation(const GLchar * name);
	uniform getUniformLocation(const GLchar *name);
	~GLProgram();
private:
	int m_programId = -1;

	 
};

