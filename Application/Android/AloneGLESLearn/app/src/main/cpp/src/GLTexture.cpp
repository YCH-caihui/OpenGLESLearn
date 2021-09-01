//
// Created by Ych-caihui on 2021/9/2.
//
#include "GLTexture.h"


void GLTexture::onSurfaceCreate()
{
    const char * vs =
     {
            "#version 300 es             \n"
            "layout(std140) uniform MatrixBlock \n"
            "{                                   \n"
            "  mat4 projection;                  \n "
            "} matrices;                          \n"
            "in vec4 v_position;                 \n"
            "in vec2 v_texCoord;                 \n"
            "out vec2 f_texCoord;                \n"
            "void main()                         \n"
            "{                                   \n"
            "   gl_Position = matrices.projection * v_position;        \n"
            "   f_texCoord = v_texCoord;         \n"
            "}                                   \n"
    };

    const char * fs =
    {
            "#version 300 es                 \n"
            "precision mediump float;         \n"
            "in vec2 f_texCoord;              \n"
            "out vec4 out_color;              \n"
            "uniform sampler2D f_texture;     \n"
            "void main()                      \n"
            "{                                \n"
            "  out_color = vec4(1.0f, 1.0f, 0.0f , 1.0f);  \n"
            "}                                \n"
    };

    m_program = new GLProgram(vs, fs);
    v_position = m_program->getAttribLocation("v_position");
    v_texCoord = m_program->getAttribLocation("v_texCoord");

    m_textureIds = new GLuint[1]();
    glGenTextures(1, m_textureIds);
    glBindTexture(GL_TEXTURE_2D, m_textureIds[0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,GL_NONE);



}


void GLTexture::onSurfaceChanged(int width, int height)
{
    m_program->useToRenderer();
    glm::mat4  proj = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 1.0f, -1.0f);
    int blockIndex = m_program->glGetUniformBlockIndex("MatrixBlock");
    GLuint blockPoint = 0;
    m_program->glUniformBlockBinding(blockIndex, blockPoint);
    m_uniform_bufferId = new GLuint[1];
    glGenBuffers(1, m_uniform_bufferId);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uniform_bufferId[0]);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), glm::value_ptr(proj), GL_DYNAMIC_READ);
    glBindBufferBase(GL_UNIFORM_BUFFER, blockPoint, m_uniform_bufferId[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}


void GLTexture::onDrawFrame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0f, 1.0f, 1.0f);


    Vertex  vertex[] =
     {

            glm::vec4(0.0f, 500.0f, 0.0f, 1.0f), glm::vec2(0.0f , 1.0f),
            glm::vec4(500.0f, 500.0f, 0.0f , 1.0f), glm::vec2(1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f),
            glm::vec4(500.0f, 0.0f, 0.0f , 1.0f), glm::vec2(1.0, 0.0f)
     };

    glEnableVertexAttribArray(v_position);
    glEnableVertexAttribArray(v_texCoord);
    glVertexAttribPointer(v_position, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), vertex);
    glVertexAttribPointer(v_texCoord, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), &vertex[0].coord);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableVertexAttribArray(v_texCoord);
    glDisableVertexAttribArray(v_position);


}