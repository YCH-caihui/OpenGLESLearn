#pragma once
#include "GLEffect.h"

class GLEffectTextureDraw : GLEffect 
{

private:
	GLProgram  * m_program;
	attribute  m_position;
	attribute  m_uv;
	uniform m_mvp;
public:

	void init() override;
	void update(int width, int height) override;
	void onDraw() override;

};