//
// Created by Ych-caihui on 2021/9/2.
//
#include "GLTextureMap.h"


void GLTextureMap::onSurfaceCreate()
{
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
            " outColor = texture(s_TextureMap, v_texCoordinate);    \n "
            "}                                                      \n"
    };

    m_program = new GLProgram(vs, fs);


}


void GLTextureMap::onSurfaceChanged(int width, int height)
{
}

void GLTextureMap::setBitmap(XBitmap *bitmap) {

}

void GLTextureMap::onDrawFrame()
{



}