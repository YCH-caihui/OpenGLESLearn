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
#include "NativeImage.h"





class GLRenderer
{
protected:
    NativeImage mNaiveImage;
public:
   virtual void onSurfaceCreate() = 0;

   void setNativeImage(int format, int width, int height, uint8_t *pData)
   {
      mNaiveImage.format = format;
      mNaiveImage.width = width;
      mNaiveImage.height = height;
      mNaiveImage.plane[0] = pData;
      NativeImageUtil::reduction(&mNaiveImage);
      initNativeImage();

   }

   virtual ~GLRenderer() {
      NativeImageUtil::freeNativeImage(&mNaiveImage);
   }

   virtual void initNativeImage() {

   }

   virtual void onSurfaceChanged(int width, int height) = 0;
   virtual void onDrawFrame() = 0;
};

#endif //ALONEGLESLEARN_GLRENDERER_H
