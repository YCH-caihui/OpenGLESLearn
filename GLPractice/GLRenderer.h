#pragma once

#include "GLEffect.h"
#include "GLEffectDefault.h"

const int ID_EFFECT_DEFAULT = 1;


class GLRenderer
{
private:
	int m_effectId;
	GLEffect* m_effect;

public:
	void enter(int id);
	void exit();

	void onSurfaceCreate();
	void onSurfaceChanged(int width, int height);
	void onDrawFrame(); 

};

