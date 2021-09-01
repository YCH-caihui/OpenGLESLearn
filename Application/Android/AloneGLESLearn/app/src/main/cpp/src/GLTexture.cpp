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
            "   gl_Position = v_position;        \n"
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
            "  out_color = texture(f_texture, f_texCoord);  \n"
            "}                                \n"
    };

    m_program = new GLProgram(vs, fs);
    v_position = m_program->getAttribLocation("v_position");
    v_texCoord = m_program->getAttribLocation("v_texCoord");


}


void GLTexture::onSurfaceChanged(int width, int height)
{
    glm::mat4  proj = glm::ortho(0, width, height, 0);
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

}