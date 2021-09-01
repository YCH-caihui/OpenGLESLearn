//
// Created by Ych-caihui on 2021/9/2.
//

#ifndef ALONEGLESLEARN_GLTEXTURE_H
#define ALONEGLESLEARN_GLTEXTURE_H

#include "GLRenderer.h"
#include "GLProgram.h"

class GLTexture : public GLRenderer
{
private:
    GLProgram * m_program;
    attribute v_position;
    attribute v_texCoord;
    bufferId  m_uniform_bufferId;

public:
    void onSurfaceCreate() override;
    void onSurfaceChanged(int width, int height) override;
    void onDrawFrame() override;

};

#endif //ALONEGLESLEARN_GLTEXTURE_H