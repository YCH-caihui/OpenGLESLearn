//
// Created by Ych-caihui on 2021/8/17.
//

#ifndef ALONEGLESLEARN_GLRENDERER_H
#define ALONEGLESLEARN_GLRENDERER_H
#include "GLProgram.h"
#include <GLES3/gl3.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "android/log.h"
#include "glm/gtc/matrix_transform.hpp"
#include "android/bitmap.h"


struct XBitmap
{
    AndroidBitmapInfo * info;
    void * addrPtr;
};

struct XNativeImage
{

};


class GLRenderer
{

public:
   virtual void onSurfaceCreate() = 0;

   virtual void setBitmap(XBitmap * bitmap) {

   }

   virtual ~GLRenderer() {}

   virtual void onSurfaceChanged(int width, int height) = 0;
   virtual void onDrawFrame() = 0;
};

#endif //ALONEGLESLEARN_GLRENDERER_H
