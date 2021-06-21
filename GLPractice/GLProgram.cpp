#include "GLProgram.h"

GLProgram::GLProgram(const GLchar* vs, const GLchar* fs)
{
	GLint  status;
	GLuint vsId = -1;
	GLuint fsId = -1;

    vsId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vsId, 1, &vs, 0);
	glCompileShader(vsId);
	glGetShaderiv(vsId, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) 
	{
		return;
	}

	fsId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsId, 1, &fs, 0);
	glCompileShader(fsId);
	glGetShaderiv(fsId, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		return;
	}

	m_programId = glCreateProgram();
	glAttachShader(m_programId, vsId);
	glAttachShader(m_programId, fsId);
	glLinkProgram(m_programId);
	glGetProgramiv(m_programId, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		return;
	}

	glDeleteShader(vsId);
	glDeleteShader(fsId);


}


void GLProgram::use()
{
   glUseProgram(m_programId);
}



GLProgram::~GLProgram()
{

}