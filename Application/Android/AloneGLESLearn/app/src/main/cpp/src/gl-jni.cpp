#include <jni.h>
#include <string>
#include <android/log.h>
#include "GLRenderer.h"


void onSurfaceCreate(JNIEnv * env, jobject object)
{
    __android_log_print(ANDROID_LOG_DEBUG, "caihui", "native_onSurfaceCreate");
}

void onSurfaceChanged(JNIEnv * env, jobject object, int width, int height)
{
    __android_log_print(ANDROID_LOG_DEBUG, "caihui", "native_onSurfaceChanged");
}

void onDrawFrame(JNIEnv * env, jobject object)
{
    __android_log_print(ANDROID_LOG_DEBUG, "caihui", "native_onDrawFrame");
}


static const JNINativeMethod nativeMethod[] = {
         "onSurfaceCreate", "()V",(void *)(onSurfaceCreate),
         "onSurfaceChanged", "(II)V",(void *)(onSurfaceChanged),
         "onDrawFrame", "()V", (void *)(onDrawFrame)

};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *javaVm, void *pVoid)
{
    JNIEnv *jniEnv = nullptr;
    if (javaVm->GetEnv(reinterpret_cast<void **>(&jniEnv), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    jclass jniClass = jniEnv->FindClass("com/caihui/alonegleslearn/GLEngine");
    jniEnv->RegisterNatives(jniClass, nativeMethod, sizeof(nativeMethod) / sizeof(JNINativeMethod));
    return JNI_VERSION_1_6;
}
