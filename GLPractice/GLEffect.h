#pragma once
#include "GLProgram.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class GLEffect 
{
public: 
	virtual void init() = 0;


	virtual void update(int width, int height) = 0;

	virtual void onDraw() = 0;
};