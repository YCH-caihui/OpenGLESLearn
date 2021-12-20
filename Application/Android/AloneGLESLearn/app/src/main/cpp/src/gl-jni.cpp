#include <jni.h>
#include <string>
#include <android/log.h>
#include "GLRenderer.h"
#include "GLHelloTriangle.h"
#include "GLUbo.h"
#include "GLTextureMap.h"

#include "android/bitmap.h"


 static const int RENDERER_TYPE_HELLO_TRIANGLE = 100;
 static const int RENDERER_TYPE_UBO = 101;
 static const int RENDERER_TYPE_TEXTURE_MAP = 102;

GLRenderer * glRenderer = nullptr;


void nativeInit(JNIEnv *env, jobject object,  int rendererType) {
    if (rendererType == RENDERER_TYPE_HELLO_TRIANGLE) {
        glRenderer = new GLHelloTriangle();
    } else if(rendererType == RENDERER_TYPE_UBO) {
        glRenderer = new GLUbo();
    } else if(rendererType == RENDERER_TYPE_TEXTURE_MAP) {
        glRenderer = new GLTextureMap();
    }
}

void setBitmapToNative(JNIEnv *env, jobject object , jobject jBitmap) {
    auto * info = new AndroidBitmapInfo();
  AndroidBitmap_getInfo(env, jBitmap, info);
  __android_log_print(ANDROID_LOG_DEBUG, "caihui", "width: %d , height: %d   stride:%d  format: %d", info->width, info->height, info->stride, info->format);

  unsigned char * addrPtr = nullptr;
  AndroidBitmap_lockPixels(env, jBitmap, (void **)&addrPtr);

  auto * xBitmap = new XBitmap();
  xBitmap->info = info;
  xBitmap->addrPtr = addrPtr;
  glRenderer->setBitmap(xBitmap);
  AndroidBitmap_unlockPixels(env, jBitmap);
  delete info;
  free(addrPtr);
  delete xBitmap;


}


void onSurfaceCreate(JNIEnv *env, jobject object) {
    if (glRenderer) {
        glRenderer->onSurfaceCreate();
    }
}

void onSurfaceChanged(JNIEnv *env, jobject object, int width, int height) {
    if (glRenderer) {
        glRenderer->onSurfaceChanged(width, height);
    }
}

void onDrawFrame(JNIEnv *env, jobject object) {
    if (glRenderer) {
        glRenderer->onDrawFrame();
    }
}


static const JNINativeMethod nativeMethod[] = {
        "nativeInit", "(I)V", (void *) (nativeInit),
        "onSurfaceCreate", "()V", (void *) (onSurfaceCreate),
        "onSurfaceChanged", "(II)V", (void *) (onSurfaceChanged),
        "onDrawFrame", "()V", (void *) (onDrawFrame),
        "setBitmapToNative","(Landroid/graphics/Bitmap;)V", (void *)(setBitmapToNative)

};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *javaVm, void *pVoid) {
    JNIEnv *jniEnv = nullptr;
    if (javaVm->GetEnv(reinterpret_cast<void **>(&jniEnv), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    jclass jniClass = jniEnv->FindClass("com/caihui/alonegleslearn/GLEngine");
    jniEnv->RegisterNatives(jniClass, nativeMethod, sizeof(nativeMethod) / sizeof(JNINativeMethod));
    return JNI_VERSION_1_6;
}
