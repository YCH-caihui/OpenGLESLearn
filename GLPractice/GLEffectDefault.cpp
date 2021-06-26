#include "GLEffectDefault.h"



void  GLEffectDefault::init()
{
	const GLchar* vs =
	{
		"#version 300 es   \n"
		"in vec4 v_position;   \n"
		"in vec4 v_color;      \n"
		"out vec4 f_color;    \n"
		"void main()          \n"
		"{                    \n"
		"  f_color = v_color;  \n"
		"  gl_Position = v_position;  \n"
		"}                           \n"
	};

	const GLchar* fs =
	{
		"#version 300 es   \n"
		"precision mediump float;  \n"
		"in vec4 f_color;       \n"
		"out vec4 o_fragColor;   \n"
		"void main()             \n"
		"{                       \n"
		" o_fragColor = f_color;  \n"
		"}                        \n"
	};
	
	m_program = new GLProgram(vs, fs);
	v_position = m_program->getAttribLocation("v_position");
	v_color = m_program->getAttribLocation("v_color");


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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0f, 1.0f, 1.0f);

	struct VC
	{
		glm::vec4 pos;
		glm::vec4 color;
	};

	VC vc[3] =
	{
		glm::vec4(0.0f, 0.5f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
		glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f), glm::vec4(1.0f,0.4, 0.0f, 1.0f),
		glm::vec4(0.5f, -0.5f, 0.0f, 1.0f), glm::vec4(0.4, 0.6, 0.0f, 1.0f)
	};

	glEnableVertexAttribArray(v_position);
	glEnableVertexAttribArray(v_color);
	glVertexAttribPointer(v_position, 4, GL_FLOAT, GL_FALSE, sizeof(VC), vc);
	glVertexAttribPointer(v_color, 4, GL_FLOAT, GL_FALSE, sizeof(VC), &vc->color);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(v_position);
	glDisableVertexAttribArray(v_color);


	
}