//
// Created by Ych-caihui on 2021/8/24.
//

#ifndef ALONEGLESLEARN_GLUBO_H
#define ALONEGLESLEARN_GLUBO_H

#include "GLProgram.h"
#include "GLRenderer.h"

class GLUbo : public GLRenderer
{
private:
    GLProgram * m_program;
    uniform m_blockIndex;
    uniform m_blockPoint = 1;
    attribute  v_position;
    attribute  v_color;
public:
    void onSurfaceCreate() override;
    void onSurfaceChanged(int width, int height) override;
    void onDrawFrame() override;
};

#endif //ALONEGLESLEARN_GLUBO_H
