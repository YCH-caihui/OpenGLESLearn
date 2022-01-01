//
// Created by Ych-caihui on 2021/9/2.
//

#ifndef ALONEGLESLEARN_GLTEXTUREMAP_H
#define ALONEGLESLEARN_GLTEXTUREMAP_H

#include "GLRenderer.h"
#include "GLProgram.h"

struct Rect {
    glm::vec4 position;
    glm::vec2 texCoordinate;
};




class GLTextureMap : public GLRenderer
{
private:

    const char * vs = {
            "#version 300 es            \n"
            "layout(location = 0) in vec4 a_position;  \n"
            "layout(location = 1) in vec2 a_texCoordinate;   \n"
            "out vec2 v_texCoordinate;                        \n"
            "void main()                                      \n"
            "{                                                \n"
            "  gl_Position = a_position;                      \n"
            "  v_texCoordinate  = a_texCoordinate;            \n"
            "}                                               \n"
    };


    const char * fs = {
            "#version 300 es                           \n"
            "precision mediump float;                   \n"
            "in vec2 v_texCoordinate;                    \n"
            "uniform sampler2D s_TextureMap;            \n"
            "layout(location = 0) out vec4 outColor;    \n"
            "void main()                                \n"
            "{                                          \n"
            " outColor = texture(s_TextureMap, v_texCoordinate);   \n "
            "}                                                    \n"
    };

     Rect * m_rect;

    GLProgram * m_program;
    attribute a_position;
    attribute a_texCoordinate;
    attribute v_texCoordinate;
    uniform  s_textureLocation;

    GLuint  m_textureId;


public:

    GLTextureMap() {
        m_rect = new Rect[] {
            glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f),   glm::vec2(0.0f, 0.0f),
            glm::vec4(-1.0f, -1.0f , 1.0f , 1.0f), glm::vec2(0.0f, 1.0f),
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),  glm::vec2(1.0f, 0.0f),
            glm::vec4(1.0f, -1.0f,  1.0f, 1.0f), glm::vec2(1.0f, 1.0f),

        };
    }

    void onSurfaceCreate() override;
    void setBitmap(XBitmap * bitmap) override;
    void onSurfaceChanged(int width, int height) override;
    void onDrawFrame() override;

    ~GLTextureMap() {
        delete[] m_rect;
    }

};

#endif //ALONEGLESLEARN_GLTEXTUREMAP_H
