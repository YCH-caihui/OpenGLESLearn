//
// Created by Ych-caihui on 2021/9/2.
//
#include "GLTextureMap.h"

#define TAG "YCH/GLTextureMap"

static const int PARAM_TYPE_INIT_BITMAP = 0;


const GLchar * vs = {
        "#version 300 es            \n"
        "layout(location = 0) in vec4 a_position;  \n"
        "layout(location = 1) in vec2 a_texCoordinate;   \n"
        "out vec2 v_texCoordinate;                        \n"
        "void main()                                      \n"
        "{                                                \n"
        "  gl_Position = a_position;                      \n"
        "  v_texCoordinate  = a_texCoordinate;            \n"
        "}                                               \n"
};


const GLchar * fs = {
        "#version 300 es                           \n"
        "precision mediump float;                   \n"
        "in vec2 v_texCoordinate;                    \n"
        "uniform sampler2D s_TextureMap;            \n"
        "layout(location = 0) out vec4 outColor;    \n"
        "void main()                                \n"
        "{                                          \n"
        " outColor = texture(s_TextureMap, v_texCoordinate);   \n "
        "}                                                    \n"
};


 GLTextureMap::GLTextureMap() {
    mTextureUnit = new TextureUnit[] {
            glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f),   glm::vec2(0.0f, 0.0f),
            glm::vec4(-1.0f, -1.0f , 1.0f , 1.0f), glm::vec2(0.0f, 1.0f),
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),  glm::vec2(1.0f, 0.0f),
            glm::vec4(1.0f, -1.0f,  1.0f, 1.0f), glm::vec2(1.0f, 1.0f),
    };
}


void GLTextureMap::onSurfaceCreate()
{
     mProgramId = ProgramUtils::create(vs, fs);
     mPositionId = glGetAttribLocation(mProgramId, "a_position");
     mTexCoordinateId  = glGetAttribLocation(mProgramId,"a_texCoordinate");
    mTextureLocationId = glGetUniformLocation(mProgramId, "s_TextureMap");

    glGenTextures(1, &mTextureBufferId);
    glBindTexture(GL_TEXTURE_2D, mTextureBufferId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

}


void GLTextureMap::onSurfaceChanged(int width, int height)
{
    glViewport(0, 0, width, height);
}



void GLTextureMap::updateParameter(JNIEnv * env, int paramType, jobject object) {
     if(paramType == PARAM_TYPE_INIT_BITMAP) {
         AndroidBitmapInfo info;
         AndroidBitmap_getInfo(env, object, &info);
         LOG_I(TAG,"<updateParameter> androidBitmapInfo flags:%d,  format:%d,  width:%d, height:%d, stride:%d",info.flags, info.format, info.width, info.height, info.stride);
         if(info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
             LOG_E(TAG, "<updateParameter>  error: Unsupported color space");
             return;
         }

         u_int8_t * pixels;
         AndroidBitmap_lockPixels(env, object, (void **)&pixels);
         NativeImage nativeImage {};
         nativeImage.format = IMAGE_FORMAT_RGBA;
         nativeImage.width = info.width;
         nativeImage.height = info.height;
         nativeImage.plane[0] = pixels;
         NativeImageUtil::reduction(&nativeImage);
         glBindTexture(GL_TEXTURE_2D, mTextureBufferId);
         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)nativeImage.width, (GLsizei)nativeImage.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nativeImage.plane[0]);
         glBindTexture(GL_TEXTURE_2D, GL_NONE);
         AndroidBitmap_unlockPixels(env, object);
     }
 }

void GLTextureMap::onDrawFrame()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glClearColor(0.4, 0.4, 0.4, 1.0);

    glUseProgram(mProgramId);
    glActiveTexture(GL_TEXTURE31);
    glBindTexture(GL_TEXTURE_2D, mTextureBufferId);
    glUniform1i(mTextureLocationId, 31);

    glEnableVertexAttribArray(mPositionId);
    glEnableVertexAttribArray(mTexCoordinateId);
    glVertexAttribPointer(mPositionId, 4, GL_FLOAT, GL_FALSE, sizeof(TextureUnit), mTextureUnit);
    glVertexAttribPointer(mTexCoordinateId, 2, GL_FLOAT, GL_FALSE, sizeof(TextureUnit), &mTextureUnit[0].texCoordinate);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(mPositionId);
    glDisableVertexAttribArray(mTexCoordinateId);
}

GLTextureMap::~GLTextureMap(){
    if(mTextureUnit != nullptr) {
        delete[] mTextureUnit;
        mTextureUnit = nullptr;
    }

    glDeleteTextures(1, &mTextureBufferId);
 }