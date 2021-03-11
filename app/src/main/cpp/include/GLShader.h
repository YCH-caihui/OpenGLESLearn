//
// Created by 杨财辉 on 3/11/21.
//

#ifndef OPENGLESLEARN_GLSHADER_H
#define OPENGLESLEARN_GLSHADER_H
#include <GLES3/gl3platform.h>
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <android/log.h>

#define TAG "GLProgram"


class ShaderId
{
public:

    int m_shaderId;

    ShaderId()
    {
        m_shaderId = -1;
    }
};


 class GLProgram
{
public:
    int m_programId;
    ShaderId m_vertex;
    ShaderId m_fragment;

    GLProgram();

     void dispatchDraw();


 protected:
    bool  createProgram(const char * vertex, const char * fragment);
    virtual const char * getVertexShader() = 0;
    virtual const char * getFragmentShader() = 0;

     virtual void begin();
     virtual void onDraw();
     virtual void end();
};


#endif //OPENGLESLEARN_GLSHADER_H
