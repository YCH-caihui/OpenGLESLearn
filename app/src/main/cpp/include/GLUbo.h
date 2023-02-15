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
    GLuint mProgramId;
    GLuint mBlockIndex;
    GLuint mBlockPoint = 1;
    GLuint  mPositionLoc;
    GLuint  mColorLoc;
public:
    void onSurfaceCreate() override;
    void onSurfaceChanged(int width, int height) override;
    void onDrawFrame() override;
};

#endif //ALONEGLESLEARN_GLUBO_H
