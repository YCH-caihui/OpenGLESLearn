#include "GLEffectBasicDraw.h"


void GLEffectBasicDraw::init()
{
	const char* vs =
	{
		"#version 300 es    \n"
		"uniform mat4 v_mvp; \n"
		"in vec4 v_position; \n"
		"in vec4 v_color;  \n"
		"out vec4 f_color; \n"
		"void main()       \n"
		"{                 \n"
		"  f_color = v_color; "
		"  gl_Position = v_mvp * v_position;   \n"
		"}                             \n"
	};

	const char* fs =
	{
		"#version 300 es  \n"
		"precision mediump  float; \n"
		"in vec4 f_color;          \n"
		"out vec4 o_color;        \n"
		"void main()              \n"
		"{                       \n"
		"  o_color = f_color;     \n"
		"}"
	};

	m_program = new GLProgram(vs, fs);
	v_position = m_program->getAttribLocation("v_position");
	v_color = m_program->getAttribLocation("v_color");
	v_mvp = m_program->getUniformLocation("v_mvp");
}


void GLEffectBasicDraw::update(int width, int height)
{
	glViewport(0, 0, width, height);
}

void GLEffectBasicDraw::onDraw()
{
	if (m_program)
	{
		m_program->use();
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

	struct VC
	{
		glm::vec4 pos; 
		glm::vec4 color;
	};

	glm::mat4 projector = glm::ortho(0.0f, 800.0f, 600.0f ,0.0f, -100.0f, 100.0f);
	

	glUniformMatrix4fv(v_mvp, 1, GL_FALSE, glm::value_ptr(projector));

	glEnableVertexAttribArray(v_position);
	glEnableVertexAttribArray(v_color);

	float   x = 0;
	float   y = 0;
	float   w = 100;
	float   h = 100;
	VC vc[4] =
	{
		glm::vec4( x, y, 0.0f, 1.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(x + w, y, 0.0f, 1.0f), glm::vec4(1.0f,0.4, 0.0f, 1.0f),
		glm::vec4(y, y + h, 0.0f, 1.0f), glm::vec4(0.4, 0.6, 0.0f, 1.0f),
		glm::vec4(x + w, y + h, 0.0f, 1.0f), glm::vec4(0.4, 0.6, 0.0f, 1.0f)
	};

	glVertexAttribPointer(v_position, 4, GL_FLOAT, GL_FALSE, sizeof(VC), vc);
	glVertexAttribPointer(v_color, 4, GL_FLOAT, GL_FALSE, sizeof(VC), &vc->color);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(v_position);
	glDisableVertexAttribArray(v_color);


}