#include "GLRenderer.h"



void GLRenderer::enter(int id) 
{
	if (m_effectId != id) {

		if (m_effect != nullptr) 
		{
			delete m_effect;
			m_effect = nullptr;
		}

		m_effectId = id;
		switch (m_effectId)
		{
		case ID_EFFECT_DEFAULT:
			m_effect = new GLEffectDefault();
			break;
		case ID_EFFECT_BASIC_DRAW:
			m_effect = new GLEffectBasicDraw();
			break;
		case ID_EFFECT_TEXTURE_DRAW:
			m_effect = new GLEffectTextureDraw();
			break;
		default:
			break;
		}
	}
}


void GLRenderer::onSurfaceCreate() 
{
	if (m_effect) 
	{
		m_effect->init();
	}
}

void GLRenderer::onSurfaceChanged(int width, int height)
{
	if (m_effect)
	{
		m_effect->update(width, height);
	}
}


void GLRenderer::onDrawFrame()
{
	if (m_effect)
	{
		m_effect->onDraw();
	}
}


void GLRenderer::exit()
{
	if (m_effect) 
	{
		delete m_effect;
		m_effect = nullptr;
	}
}