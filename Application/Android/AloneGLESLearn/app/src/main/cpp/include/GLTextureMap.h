//
// Created by Ych-caihui on 2021/9/2.
//

#ifndef ALONEGLESLEARN_GLTEXTUREMAP_H
#define ALONEGLESLEARN_GLTEXTUREMAP_H

#include "GLRenderer.h"
#include "GLProgram.h"


class GLTextureMap : public GLRenderer
{
private:
    GLProgram * m_program;

public:
    void onSurfaceCreate() override;
    void setBitmap(XBitmap * bitmap) override;
    void onSurfaceChanged(int width, int height) override;
    void onDrawFrame() override;

};

#endif //ALONEGLESLEARN_GLTEXTUREMAP_H
