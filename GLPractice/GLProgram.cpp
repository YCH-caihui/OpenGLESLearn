#include "GLProgram.h"

GLProgram::GLProgram(const GLchar* vs, const GLchar* fs)
{
	GLint  parame = -1;
	GLuint vsId = -1;
	GLuint fsId = -1;

    vsId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vsId, 1, &vs, 0);
	glCompileShader(vsId);
	glGetShaderiv(vsId, GL_COMPILE_STATUS, &parame);
	if (parame != GL_TRUE)
	{
		glGetShaderiv(vsId, GL_INFO_LOG_LENGTH, &parame);
		GLchar* strInfoLog = new GLchar[parame + 1];
		glGetShaderInfoLog(vsId, parame, nullptr, strInfoLog);
		glDeleteShader(vsId);
		delete[] strInfoLog;
		return;
	}

	fsId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsId, 1, &fs, 0);
	glCompileShader(fsId);
	glGetShaderiv(fsId, GL_COMPILE_STATUS, &parame);
	if (parame != GL_TRUE)
	{
		return;
	}

	m_programId = glCreateProgram();
	glAttachShader(m_programId, vsId);
	glAttachShader(m_programId, fsId);
	glLinkProgram(m_programId);
	glGetProgramiv(m_programId, GL_LINK_STATUS, &parame);
	if (parame != GL_TRUE)
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

attribute GLProgram::getAttribLocation(const char * name)
{
	return glGetAttribLocation(m_programId, name);
}

uniform GLProgram::getUniformLocation(const char* name)
{
	return glGetAttribLocation(m_programId, name);
}


GLProgram::~GLProgram()
{
	glDeleteProgram(m_programId);
}