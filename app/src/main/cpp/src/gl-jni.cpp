#include <jni.h>
#include <string>
#include <android/log.h>
#include "GLRenderer.h"
#include "GLHelloTriangle.h"
#include "GLUbo.h"
#include "GLTextureMap.h"
#include "GLYuvMap.h"
#include "GLVboEBoVao.h"

#include "android/bitmap.h"


 static const int RENDERER_TYPE_HELLO_TRIANGLE = 100;
 static const int RENDERER_TYPE_UBO = 101;
 static const int RENDERER_TYPE_TEXTURE_MAP = 102;
 static const int RENDERER_TYPE_YUV_MAP = 103;
 static const int RENDERER_TYPE_VBO_EBO_VAO = 104;

GLRenderer * glRenderer = nullptr;


void nativeInit(JNIEnv *env, jobject object,  int rendererType) {

    if(glRenderer != nullptr) {
        delete glRenderer;
    }
    if (rendererType == RENDERER_TYPE_HELLO_TRIANGLE) {
        glRenderer = new GLHelloTriangle();
    } else if(rendererType == RENDERER_TYPE_UBO) {
        glRenderer = new GLUbo();
    } else if(rendererType == RENDERER_TYPE_TEXTURE_MAP) {
        glRenderer = new GLTextureMap();
    } else if(rendererType == RENDERER_TYPE_YUV_MAP) {
        glRenderer = new GLYuvMap();
    } else if(rendererType == RENDERER_TYPE_VBO_EBO_VAO) {
        glRenderer = new GLYboEBoVao();
    }
}


void setNativeImage(JNIEnv * env, jobject object, jint format, jint width, jint height, jbyteArray byteArray) {
    int length =  env->GetArrayLength(byteArray);
    auto * buf = new u_int8_t[length];
    env->GetByteArrayRegion(byteArray, 0, length, reinterpret_cast<jbyte *>(buf) );
    glRenderer->setNativeImage(format, width, height, buf);
    env->DeleteLocalRef(byteArray);

}

void updateParameter(JNIEnv * env, jobject obj, jint  paramType, jobject paramObj) {
    glRenderer->updateParameter(env, paramType, paramObj);
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
        "updateParameter","(ILjava/lang/Object;)V", (void *)(updateParameter),
        "setNativeImage", "(III[B)V",(void *)setNativeImage,

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
