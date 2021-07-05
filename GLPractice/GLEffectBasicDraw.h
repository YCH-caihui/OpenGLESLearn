#pragma once
#include "GLEffect.h"

class GLEffectBasicDraw : public GLEffect
{

private:
	GLProgram* m_program;
	attribute v_position;
	attribute v_color;
	uniform v_mvp;


public:
	void init() override;
	void update(int width, int height) override;
	void onDraw() override;

};