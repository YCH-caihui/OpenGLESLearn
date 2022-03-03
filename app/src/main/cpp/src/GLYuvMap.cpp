//
// Created by Ych-caihui on 2022/2/17.
//
#include "GLYuvMap.h"

void GLYuvMap::onSurfaceCreate()
{
    mProgram= new GLProgram(vs, fs);
    mPositionIndex = mProgram->getAttribLocation("a_position");
    mTexCoordinateIndex = mProgram->getAttribLocation("a_texCoordinate");
    mYTextureIndex = mProgram->getUniformLocation("y_texture");
    mUvTextureIndex = mProgram->getUniformLocation("uv_texture");

    glGenTextures(2, mTextureId);
    glBindTexture(GL_TEXTURE_2D, *mTextureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    glBindTexture(GL_TEXTURE_2D, *(mTextureId + 1));
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



void GLYuvMap::initNaiveImage()
{
    glBindTexture(GL_TEXTURE_2D, *mTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, mNaiveImage.width, mNaiveImage.height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, mNaiveImage.plane[0]);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    glBindTexture(GL_TEXTURE_2D, *(mTextureId + 1));
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, mNaiveImage.width >> 1, mNaiveImage.height >> 1, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, mNaiveImage.plane[1]);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

}

void GLYuvMap::onDrawFrame()
{
    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    mProgram->useToRenderer();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *mTextureId);
    glUniform1i(mYTextureIndex, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, *(mTextureId + 1));
    glUniform1i(mUvTextureIndex, 1);

    glEnableVertexAttribArray(mPositionIndex);
    glEnableVertexAttribArray(mTexCoordinateIndex);
    glVertexAttribPointer(mPositionIndex, 4, GL_FLOAT, GL_FALSE, sizeof(YUVRect), mRect);
    glVertexAttribPointer(mTexCoordinateIndex, 2, GL_FLOAT, GL_FALSE, sizeof(YUVRect), &(mRect[0].texCoordinate));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
    glDisableVertexAttribArray(mPositionIndex);
    glDisableVertexAttribArray(mTexCoordinateIndex);

}