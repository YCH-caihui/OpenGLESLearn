#include <jni.h>
#include <string>
#include "GLMath.h"
#include "include/GLShader.h"




extern "C"
JNIEXPORT void JNICALL
Java_com_caihui_opengleslearn_view_GLRootView_init(JNIEnv *env, jobject thiz, jint gl_type) {
}



extern "C" JNIEXPORT void JNICALL
Java_com_caihui_opengleslearn_view_GLRootView_onSurfaceCreated(
        JNIEnv* env,
        jobject /* this */) {

}

extern "C"
JNIEXPORT void JNICALL
Java_com_caihui_opengleslearn_view_GLRootView_onSurfaceChanged(JNIEnv *env, jobject thiz,
                                                               jint width, jint height) {

}

extern "C"
JNIEXPORT void JNICALL
Java_com_caihui_opengleslearn_view_GLRootView_onDrawFrame(JNIEnv *env, jobject thiz) {

}

