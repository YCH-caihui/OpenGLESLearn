//
// Created by Ych-caihui on 2022/2/17.
//
#include "GLYuvMap.h"

void GLYuvMap::onSurfaceCreate()
{
    m_programId = new GLProgram(vs, fs);
    m_positionId = m_programId->getAttribLocation("a_position");
    m_texCoordinateId = m_programId->getAttribLocation("a_texCoordinate");
    m_yTextureId = m_programId->getUniformLocation("y_texture");
    m_uvTextureId = m_programId->getUniformLocation("uv_texture");
}

void GLYuvMap::onSurfaceChanged(int width, int height)
{
    glViewport(0, 0, width, height);
}

void GLYuvMap::onDrawFrame()
{

}