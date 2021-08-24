//
// Created by Ych-caihui on 2021/8/24.
//
#include "GLUbo.h"


void GLUbo::onSurfaceCreate()
{

    const char * vertexShader =
     {
             "#version 300 es        \n"
             "uniform MatrixBlock     \n"
             "{                       \n"
             "  mat4 projection;      \n"
             "} matrices;              \n"
             "in vec4 v_position;     \n"
             "in vec4 v_color;        \n"
             "out vec4 f_color;       \n"
             "void main()             \n"
             "{                       \n"
             "   gl_Position = matrices.projection * v_position;  \n "
             "   f_color = v_color;                    \n"
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
    glGetUniformBlockIndex(    )

}

void GLUbo::onSurfaceChanged(int width, int height)
{

}


void GLUbo::onDrawFrame()
{

}