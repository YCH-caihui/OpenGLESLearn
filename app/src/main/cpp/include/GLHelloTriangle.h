//
// Created by Ych-caihui on 2021/8/17.
//

#ifndef ALONEGLESLEARN_GLHELLOTRIANGLE_H
#define ALONEGLESLEARN_GLHELLOTRIANGLE_H

#include "GLRenderer.h"
#include "GLProgram.h"



class GLHelloTriangle : public GLRenderer {
private:
    GLuint mProgramId;
    GLint mPositionId;
    GLint mColorId;
    GLint mMvpId;
    int mWidth;
    int mHeight;
public:
    void onSurfaceCreate() override;

    void onSurfaceChanged(int width, int height) override;

    void onDrawFrame() override;
};

#endif //ALONEGLESLEARN_GLHELLOTRIANGLE_H
