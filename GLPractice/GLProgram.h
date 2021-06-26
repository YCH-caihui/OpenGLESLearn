#pragma once

#include <GLES3/gl3.h>
#include <stdlib.h>



class GLProgram
{
public:
	GLProgram(const GLchar* vs, const GLchar* fs);
	void use();

	~GLProgram();
private:
	int m_programId = -1;

	 
};

