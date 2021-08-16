//
// Created by Ych-caihui on 2021/8/17.
//

#ifndef ALONEGLESLEARN_GLHELLOTRIANGLE_H
#define ALONEGLESLEARN_GLHELLOTRIANGLE_H
#include "GLRenderer.h"
#include "GLProgram.h"
class GLHelloTriangle : GLRenderer
{
private:
    GLProgram * m_program;
public:
     void onSurfaceCreate() override;
     void onSurfaceChanged(int width, int height) override;
     void onDrawFrame() override;
};
#endif //ALONEGLESLEARN_GLHELLOTRIANGLE_H
