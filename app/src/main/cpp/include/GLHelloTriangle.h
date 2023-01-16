//
// Created by Ych-caihui on 2021/8/17.
//

#ifndef ALONEGLESLEARN_GLHELLOTRIANGLE_H
#define ALONEGLESLEARN_GLHELLOTRIANGLE_H

#include "GLRenderer.h"
#include "GLProgram.h"



class GLHelloTriangle : public GLRenderer {
private:
    GLuint mProgram;
    GLint mPositionLoc;
    GLint mColorLoc;
    GLint mMvpLoc;
    int mWidth;
    int mHeight;

    void drawTriangle(const float * vertex) const;
public:
    void onSurfaceCreate() override;

    void onSurfaceChanged(int width, int height) override;

    void onDrawFrame() override;
};

#endif //ALONEGLESLEARN_GLHELLOTRIANGLE_H
