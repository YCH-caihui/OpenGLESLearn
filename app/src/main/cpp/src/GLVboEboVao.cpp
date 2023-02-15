//
// Created by Ych-caihui on 2022/3/12.
//
#include "GLVboEboVao.h"


#define TAG "YCH/GLVboEboBao"

void GLYboEBoVao::onSurfaceCreate() {
    mProgram = new GLProgram(vs, fs);
    mPositionIndex = mProgram->getAttribLocation("a_position");
    mTexCoordinateIndex  = mProgram->getAttribLocation("a_texCoordinate");
    mTextureIndex = mProgram->getUniformLocation("s_textureMap");

    glGenTextures(1, &mTextureId);
    glBindTexture(GL_TEXTURE_2D, mTextureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    //创建2个vbo（EBO 实际上跟VBO 一样，只是按照用途的另一种称呼）
    glGenBuffers(2, mVboIds);
    //绑定一个VBO，拷贝顶点数组到显存
    glBindBuffer(GL_ARRAY_BUFFER, mVboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VBORect) * 4, mRect, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

    //绑定第二个vbo（EBO）, 拷贝索引元素
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndices), mIndices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_NONE);


    //创建并绑定VAO
    glGenVertexArrays(1, &mVaoId);
    glBindVertexArray(mVaoId);
    //在绑定 VAO之后， 操作VBO, 当前VAO会记录VBO的操作
    glBindBuffer(GL_ARRAY_BUFFER, mVboIds[0]);
    glEnableVertexAttribArray(mPositionIndex);
    glEnableVertexAttribArray(mTexCoordinateIndex);
    glVertexAttribPointer(mPositionIndex, 3, GL_FLOAT, GL_FALSE, sizeof(VBORect), (const void *)0);
    glVertexAttribPointer(mTexCoordinateIndex, 2, GL_FLOAT ,GL_FALSE, sizeof(VBORect),  (const void *)sizeof(mRect->position));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVboIds[1]);
    glBindVertexArray(GL_NONE);




}



void GLYboEBoVao::updateParameter(JNIEnv * env, int paramType, jobject paramObj) {

    AndroidBitmapInfo info;
    AndroidBitmap_getInfo(env, paramObj, &info);
    LOG_I(TAG,"<updateParameter> androidBitmapInfo flags:%d,  format:%d,  width:%d, height:%d, stride:%d",info.flags, info.format, info.width, info.height, info.stride);
    if(info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOG_E(TAG, "<updateParameter>  error: Unsupported color space");
        return;
    }

    u_int8_t * pixels;
    AndroidBitmap_lockPixels(env, paramObj, (void **)&pixels);
    NativeImage nativeImage{};
    nativeImage.format = IMAGE_FORMAT_RGBA;
    nativeImage.width = info.width;
    nativeImage.height = info.height;
    nativeImage.plane[0] = pixels;
    NativeImageUtil::reduction(&nativeImage);
    glBindTexture(GL_TEXTURE_2D, mTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)nativeImage.width, (GLsizei)nativeImage.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nativeImage.plane[0]);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
}

void GLYboEBoVao::onSurfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
}

void GLYboEBoVao::onDrawFrame() {


    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glClearColor(0.4, 0.4, 0.4, 1.0);

    mProgram->useToRenderer();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureId);
    glUniform1i(mTextureIndex, 0);

    glBindVertexArray(mVaoId);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (const void *)0);
}
