//
// Created by Ych-caihui on 2021/9/2.
//
#include "GLTextureMap.h"


void GLTextureMap::onSurfaceCreate()
{
    m_program = new GLProgram(vs, fs);
    a_position =  m_program->getAttribLocation("a_position");
    a_texCoordinate = m_program->getAttribLocation("a_texCoordinate");
    s_textureLocation = m_program->getUniformLocation("s_TextureMap");

    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
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


void GLTextureMap::initNaiveImage()
{
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mNaiveImage.width, mNaiveImage.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, mNaiveImage.plane[0]);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

}

void GLTextureMap::onDrawFrame()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glClearColor(0.4, 0.4, 0.4, 1.0);

    m_program->useToRenderer();
    glActiveTexture(GL_TEXTURE31);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glUniform1i(s_textureLocation, 31);

    glEnableVertexAttribArray(a_position);
    glEnableVertexAttribArray(a_texCoordinate);
    glVertexAttribPointer(a_position, 4, GL_FLOAT, GL_FALSE, sizeof(Rect), m_rect);
    glVertexAttribPointer(a_texCoordinate, 2, GL_FLOAT, GL_FALSE, sizeof(Rect), &m_rect[0].texCoordinate);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(a_position);
    glDisableVertexAttribArray(a_texCoordinate);
}