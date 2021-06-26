#pragma once
#include "GLProgram.h"

class GLEffect 
{
public: 
	virtual void init() = 0;

	virtual void update(int width, int height) = 0;

	virtual void onDraw() = 0;
};