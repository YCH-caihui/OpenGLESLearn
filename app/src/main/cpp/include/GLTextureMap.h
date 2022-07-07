//
// Created by Ych-caihui on 2021/9/2.
//

#ifndef ALONEGLESLEARN_GLTEXTUREMAP_H
#define ALONEGLESLEARN_GLTEXTUREMAP_H

#include "GLRenderer.h"
#include "GLProgram.h"

struct TextureUnit {
    glm::vec4 position;
    glm::vec2 texCoordinate;
};


class GLTextureMap : public GLRenderer
{
private:


     TextureUnit * mTextureUnit;

    GLuint  mProgramId;
    GLint   mPositionId;
    GLint  mTexCoordinateId;
    GLint  mTextureLocationId;
    GLuint  mTextureBufferId;


public:

    GLTextureMap();

    void onSurfaceCreate() override;
    void onSurfaceChanged(int width, int height) override;
    void onDrawFrame() override;

    ~GLTextureMap();

    void initNativeImage() override;
};

#endif //ALONEGLESLEARN_GLTEXTUREMAP_H
