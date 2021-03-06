#pragma once

#include "GLEffect.h"
#include "GLEffectDefault.h"
#include "GLEffectBasicDraw.h"
#include "GLEffectTextureDraw.h"

const int ID_EFFECT_DEFAULT = 1;
const int ID_EFFECT_BASIC_DRAW = 2;
const int ID_EFFECT_TEXTURE_DRAW = 3;



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

