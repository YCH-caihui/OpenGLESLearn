#pragma once
#include "GLEffect.h"

class GLEffectDefault : public GLEffect
{

private: 
	GLProgram* m_program;
	attribute v_position;
	attribute v_color;

public:
	 void init() override;

	 void update(int width, int height) override;

	 void onDraw() override;

};

