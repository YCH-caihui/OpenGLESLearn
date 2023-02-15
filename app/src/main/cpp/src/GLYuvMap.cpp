//
// Created by Ych-caihui on 2022/2/17.
//
#include "GLYuvMap.h"

#define TAG "YCH/GLYuvMap"

static const int PARAM_TYPE_INIT_YUV = 0;

static const char * vs = {
        "#version 300 es           \n"
        "layout(location = 0) in vec4 a_position;   \n"
        "layout(location = 1) in vec2 a_texCoordinate;  \n"
        "out vec2 v_texCoordinate;                       \n"
        "void main()                                     \n"
        "{                                               \n"
        "   gl_Position = a_position;                   \n"
        "   v_texCoordinate  = a_texCoordinate;         \n"
        "}                                              \n"
};

static const char * fs = {
        "#version 300 es                              \n"
        "precision mediump float;                     \n"
        "in vec2 v_texCoordinate;                     \n"
        "layout(location = 0) out vec4 outColor;      \n"
        "uniform sampler2D y_texture;                 \n"
        "uniform sampler2D uv_texture;                \n"
        "void main()                                  \n"
        "{                                            \n"
        "   vec3 yuv;                                 \n"
        "  yuv.x = texture(y_texture, v_texCoordinate).r;  \n"
        "  yuv.y = texture(uv_texture, v_texCoordinate).r - 0.5; \n"
        "  yuv.z = texture(uv_texture, v_texCoordinate).a - 0.5; \n"
        " highp vec3 rgb = mat3(    1, 1, 1,                   \n"
        "                          0, -0.344, 1.770,          \n"
        "                          1.403, -0.714, 0) * yuv;    \n"
        " outColor = vec4(rgb, 1);                            \n"
        "}                                                    \n"

};

GLYuvMap::GLYuvMap() {
    mRect = new YUVRect[] {
            glm::vec4(-1.0f,  0.78f, 0.0f, 1.0f),   glm::vec2(0.0f, 0.0f),
            glm::vec4(-1.0f, -0.78f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f),
            glm::vec4(1.0f,  -0.78f, 0.0f, 1.0f),  glm::vec2(1.0f, 1.0f),
            glm::vec4(1.0f,   0.78f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f),
    };
}

void GLYuvMap::onSurfaceCreate()
{
    mProgramId = ProgramUtils::create(vs, fs);
    mPositionId = glGetAttribLocation(mProgramId, "a_position");
    mTexCoordinateId = glGetAttribLocation(mProgramId, "a_texCoordinate");
    mYTextureId = glGetUniformLocation(mProgramId, "y_texture");
    mUvTextureId = glGetUniformLocation(mProgramId, "uv_texture");

    glGenTextures(2, mTextureBufferId);
    glBindTexture(GL_TEXTURE_2D, *mTextureBufferId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    glBindTexture(GL_TEXTURE_2D, *(mTextureBufferId + 1));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);


}

void GLYuvMap::onSurfaceChanged(int width, int height)
{
    glViewport(0, 0, width, height);
}



void GLYuvMap::updateParameter(JNIEnv * env, int paramType, jobject paramObj) {

    if(paramType == PARAM_TYPE_INIT_YUV) {
      jclass  yuvParamClass =  env->GetObjectClass(paramObj);
      int format = env->GetIntField(paramObj, env->GetFieldID(yuvParamClass, "format", "I"));
      int width = env->GetIntField(paramObj, env->GetFieldID(yuvParamClass, "width", "I"));
      int height = env->GetIntField(paramObj, env->GetFieldID(yuvParamClass, "height", "I"));
      auto yuvData = (jbyteArray)env->GetObjectField(paramObj, env->GetFieldID(
              yuvParamClass, "yuvData", "[B"));
      int yuvDataLength = env->GetArrayLength(yuvData);

      auto  * tempYuvBuffers = new jbyte[yuvDataLength]();
      env->GetByteArrayRegion(yuvData, 0, yuvDataLength, tempYuvBuffers);
      NativeImage naiveImage{};
      naiveImage.format = format;
      naiveImage.width = width;
      naiveImage.height = height;
      naiveImage.plane[0] = (u_int8_t *)tempYuvBuffers;
      NativeImageUtil::reduction(&naiveImage);

      glBindTexture(GL_TEXTURE_2D, *mTextureBufferId);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, (GLsizei)naiveImage.width, (GLsizei)naiveImage.height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, naiveImage.plane[0]);
      glBindTexture(GL_TEXTURE_2D, GL_NONE);

      glBindTexture(GL_TEXTURE_2D, *(mTextureBufferId + 1));
      glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, (GLsizei)naiveImage.width >> 1, (GLsizei)naiveImage.height >> 1, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, naiveImage.plane[1]);
      glBindTexture(GL_TEXTURE_2D, GL_NONE);

      delete [] tempYuvBuffers;
    }


}

void GLYuvMap::onDrawFrame()
{
    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glUseProgram(mProgramId);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *mTextureBufferId);
    glUniform1i(mYTextureId, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, *(mTextureBufferId + 1));
    glUniform1i(mUvTextureId, 1);

    glEnableVertexAttribArray(mPositionId);
    glEnableVertexAttribArray(mTexCoordinateId);
    glVertexAttribPointer(mPositionId, 4, GL_FLOAT, GL_FALSE, sizeof(YUVRect), mRect);
    glVertexAttribPointer(mTexCoordinateId, 2, GL_FLOAT, GL_FALSE, sizeof(YUVRect), &(mRect[0].texCoordinate));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
    glDisableVertexAttribArray(mPositionId);
    glDisableVertexAttribArray(mTexCoordinateId);

}