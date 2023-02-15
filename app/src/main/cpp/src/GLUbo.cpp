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


    mProgramId = ProgramUtils::create(vertexShader, fragmentShader);


    mPositionLoc = glGetAttribLocation(mProgramId, "v_position");
    mColorLoc = glGetAttribLocation(mProgramId, "v_color");
   int maxVertexUniform, maxFragmentUniform;
   glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &maxVertexUniform);
   glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &maxFragmentUniform);

   __android_log_print(ANDROID_LOG_DEBUG, "GLUbo", "gl_max_vertex_uniform_components:%d  gl_max_fragment_uniform_components:%d", maxVertexUniform, maxFragmentUniform);

}

void GLUbo::onSurfaceChanged(int width, int height)
{

    glm::mat4  proj = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 1.0f, -1.0f);
    mBlockIndex = glGetUniformBlockIndex(mProgramId, "MatrixBlock");
    glUniformBlockBinding(mProgramId, mBlockIndex, mBlockPoint);
    GLuint uboId = -1;
    glGenBuffers(1, &uboId);
    glBindBuffer(GL_UNIFORM_BUFFER, uboId);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(proj) + sizeof(glm::vec4), nullptr, GL_DYNAMIC_READ);
   // glBindBufferBase(GL_UNIFORM_BUFFER, m_blockPoint, uboId);
    glBindBufferRange(GL_UNIFORM_BUFFER, mBlockPoint, uboId, 0,  sizeof(glm::mat4) + sizeof(glm::vec4));
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
    glUseProgram(mProgramId);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    const float triangle[] = {
            50, 0.0f , 0.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 100, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
            100, 100, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f
    };


    glEnableVertexAttribArray(mPositionLoc);
    glEnableVertexAttribArray(mColorLoc);
    glVertexAttribPointer(mPositionLoc, 4, GL_FLOAT, GL_FALSE, sizeof(float ) *  8, triangle);
    glVertexAttribPointer(mColorLoc, 4, GL_FLOAT, GL_FALSE, sizeof(float ) * 8, &triangle[4]);
    glDrawArrays(GL_TRIANGLES, 0, 3 );
    glDisableVertexAttribArray(mPositionLoc);
    glDisableVertexAttribArray(mColorLoc);

}