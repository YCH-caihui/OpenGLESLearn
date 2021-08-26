//
// Created by Ych-caihui on 2021/8/24.
//
#include "GLUbo.h"


void GLUbo::onSurfaceCreate()
{

    const char * vertexShader =
     {
             "#version 300 es        \n"
             "layout (std140) uniform MatrixBlock     \n"
             "{                       \n"
             "  mat4 projection;      \n"
             "  vec4 color;           \n"
             "} matrices;              \n"
             "in vec4 v_position;     \n"
             "in vec4 v_color;        \n"
             "out vec4 f_color;       \n"
             "void main()             \n"
             "{                       \n"
             "   gl_Position = matrices.projection * v_position;  \n "
             "   f_color = matrices.color;                    \n"
             "}                                        \n"
     };

    const char * fragmentShader =
    {
            "#version 300 es           \n"
            "precision mediump float;  \n"
            "in vec4 f_color;          \n"
            "out vec4 o_color;         \n"
            "void main()               \n"
            "{                         \n"
            "  o_color = f_color;      \n "
            "}                         \n"
    };
    m_program = new GLProgram(vertexShader, fragmentShader);


   v_position = m_program->getAttribLocation("v_position");
   v_color = m_program->getAttribLocation("v_color");



}

void GLUbo::onSurfaceChanged(int width, int height)
{
    m_program->useToRenderer();
    glm::mat4  proj = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 1.0f, -1.0f);
    m_blockIndex = m_program->glGetUniformBlockIndex("MatrixBlock");
    m_program->glUniformBlockBinding(m_blockIndex, m_blockPoint);
    GLuint uboId = -1;
    glGenBuffers(1, &uboId);
    glBindBuffer(GL_UNIFORM_BUFFER, uboId);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(proj) + sizeof(glm::vec4), nullptr, GL_DYNAMIC_READ);
   // glBindBufferBase(GL_UNIFORM_BUFFER, m_blockPoint, uboId);
    glBindBufferRange(GL_UNIFORM_BUFFER, m_blockPoint, uboId, 0,  sizeof(glm::mat4) + sizeof(glm::vec4));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glm::vec4 color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    glBindBuffer(GL_UNIFORM_BUFFER, uboId);
    glBufferSubData(GL_UNIFORM_BUFFER, 0 , sizeof(glm::mat4), glm::value_ptr(proj));
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::vec4), glm::value_ptr(color));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBuffer(GL_UNIFORM_BUFFER, uboId);
    glm::vec4 as = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::vec4), glm::value_ptr(as));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}


void GLUbo::onDrawFrame()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    const float triangle[] = {
            50, 0.0f , 0.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 100, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
            100, 100, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f
    };


    glEnableVertexAttribArray(v_position);
    glEnableVertexAttribArray(v_color);
    glVertexAttribPointer(v_position, 4, GL_FLOAT, GL_FALSE, sizeof(float ) *  8, triangle);
    glVertexAttribPointer(v_color, 4, GL_FLOAT, GL_FALSE, sizeof(float ) * 8, &triangle[4]);
    glDrawArrays(GL_TRIANGLES, 0, 3 );
    glDisableVertexAttribArray(v_position);
    glDisableVertexAttribArray(v_color);

}