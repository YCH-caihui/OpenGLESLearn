#include "GLEffectDefault.h"

void  GLEffectDefault::init()
{
	const GLchar* fs =
	{
		"#version 300 es   "
		"in vec4 v_position;  "
		"in vec4 v_color;     "
		"out vec4 f_color;    "
		"void main()          "
		"{                    "
		"  f_color = v_color;  "
		"  gl_Position = v_position;  "
		"}                           "
	};

	const GLchar* vs =
	{
		"#version 300 es"
		"precision mediump float;"
		"in vec4 f_color;  "
		"out vec4 o_fragColor;"
		"void main() "
		"{"
		" o_fragColor = f_color; "
		"}"
	};
	
	m_program = new GLProgram(fs, vs);

}

void  GLEffectDefault::update(int width, int height)
{
	glViewport(0, 0, width, height);
}


void GLEffectDefault::onDraw() 
{
	if (m_program)
	{
		m_program->use();
	}
}