//
// Created by Ych-caihui on 2021/9/2.
//

#ifndef ALONEGLESLEARN_GLTEXTURE_H
#define ALONEGLESLEARN_GLTEXTURE_H

#include "GLRenderer.h"
#include "GLProgram.h"

struct Vertex
{
    glm::vec4  position;
    glm::vec2  coord;
};

class GLTexture : public GLRenderer
{
private:
    GLProgram * m_program;
    attribute v_position;
    attribute v_texCoord;
    bufferId  m_uniform_bufferId;
    textureId m_textureIds;
    uniform  f_texture;
    int m_width;
    int m_height;

public:
    void onSurfaceCreate() override;
    void setBitmap(XBitmap * bitmap) override;
    void onSurfaceChanged(int width, int height) override;
    void onDrawFrame() override;

};

#endif //ALONEGLESLEARN_GLTEXTURE_H
