//
// Created by Ych-caihui on 2021/8/17.
//

#ifndef ALONEGLESLEARN_GLHELLOTRIANGLE_H
#define ALONEGLESLEARN_GLHELLOTRIANGLE_H
#include "GLRenderer.h"
#include "GLProgram.h"


#define TAG "GLHelloTriangle"

class GLHelloTriangle : public GLRenderer
{
private:
    GLProgram * m_program;
    attribute  v_position;
    attribute  v_color;
    uniform  v_mvp;
    int m_width;
    int m_height;
public:
     void onSurfaceCreate() override;
     void onSurfaceChanged(int width, int height) override;
     void onDrawFrame() override;
};
#endif //ALONEGLESLEARN_GLHELLOTRIANGLE_H
