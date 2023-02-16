//
// Created by Ych-caihui on 2022/2/17.
//

#ifndef ALONEGLESLEARN_GLYUVMAP_H
#define ALONEGLESLEARN_GLYUVMAP_H

#include "GLRenderer.h"
#include "GLProgram.h"
#include "NativeImage.h"

 struct YUVRect {
    glm::vec4 position;
    glm::vec2 texCoordinate;
};

class GLYuvMap : public GLRenderer
{

private:
    YUVRect * mRect;
    GLuint mProgramId{};
    GLint mPositionId{};
    GLint mTexCoordinateId{};
    GLint mYTextureId{};
    GLint mUvTextureId{};
    GLuint  *mTextureBufferId = new GLuint[2];





public:

    GLYuvMap();

    void onSurfaceCreate() override;
    void onSurfaceChanged(int width, int height) override;
    void onDrawFrame() override;
    void updateParameter(JNIEnv * env, int paramType, jobject paramObj) override;
    ~GLYuvMap() {
        if(mTextureBufferId != NULL) {
            delete[] mTextureBufferId;
        }
    }
};

#endif //ALONEGLESLEARN_GLYUVMAP_H
