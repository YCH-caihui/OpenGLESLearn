#include "GLEffectTextureDraw.h"


void GLEffectTextureDraw::init() 
{
	const char* vs =
	{
		"#version 300 es     \n"
		"uniform mat4 _mvp;  \n"
		"in vec2  _position;   \n"
		"in vec2  _uv;          \n"
		"out vec2 _outUV;       \n"
		"void main()           \n"
		"{                     \n"
		"   vec4  pos = vec4(_position, 0, 1);  \n"
		"   _outUV  = _uv;           \n "
		"   gl_Position = _mvp * pos;   \n"
		"}"
	};

	const char* fs =
	{
		"#version 300 es    \n"
		"uniform sampler2D _texture;  \n"
		"int vec2 _outUV;             \n"
		"out vec4 _fragColor;         \n"
		"void main()                   \n"
		"{                             \n"
		"  _fragColor = texture2D(_texture, _outUV);  \n"
		"}"
	};

	m_program = new GLProgram(vs, fs);
	m_position = m_program->getAttribLocation("_position");

}


void GLEffectTextureDraw::update(int width, int height)
{

}


void GLEffectTextureDraw::onDraw()
{

}