//
// Created by chyan on 2023/2/17.
//

#ifndef OPENGLESLEARN_GLTRANSFORMSAMPLE_H
#define OPENGLESLEARN_GLTRANSFORMSAMPLE_H
#include "GLRenderer.h"
#include "GLProgram.h"

class GLTransformSample : public GLRenderer {

private:
    GLuint mProgramId;
    GLint mPositionLoc;
    GLint mTexCoordinateLoc;
    GLint mTextureLoc;
    GLint mTextureId;



public:

    GLTransformSample();
    void onSurfaceCreate() override;
    void onSurfaceChanged(int width, int height) override;
    void onDrawFrame() override;
    void updateParameter(JNIEnv * env, int paramType, jobject object) override;
    ~GLTransformSample();
};

#endif //OPENGLESLEARN_GLTRANSFORMSAMPLE_H
