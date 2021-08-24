//
// Created by Ych-caihui on 2021/8/17.
//

#include "GLHelloTriangle.h"

void GLHelloTriangle::onSurfaceCreate() {
    const char *vertexShader =
            {
                    "#version 300 es       \n"
                    "in vec4 v_position;   \n"
                    "in vec4 v_color;      \n"
                    "uniform mat4 v_mvp;    \n"
                    "out vec4 f_color;     \n"
                    "void main()           \n"
                    "{                     \n"
                    "   f_color = v_color;   \n"
                    "   gl_Position = v_mvp * v_position; \n"
                    "}                           \n"
            };
    const char *fragmentShader =
            {
                    "#version 300 es            \n"
                    "precision mediump float;   \n"
                    "in vec4 f_color;          \n"
                    "out vec4 o_color;          \n"
                    "void  main()               \n"
                    "{                          \n"
                    "  o_color = f_color;       \n"
                    "}                          \n"
            };


    m_program = new GLProgram(vertexShader, fragmentShader);
    v_position = m_program->getAttribLocation("v_position");
    v_color = m_program->getAttribLocation("v_color");
    v_mvp = m_program->getUniformLocation("v_mvp");

}

void GLHelloTriangle::onSurfaceChanged(int width, int height) {
    m_width = width;
    m_height = height;
    glViewport(0, 0, width, height);
}


void GLHelloTriangle::onDrawFrame() {
    const float triangle[] = {
            50, 0.0f , 0.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
          0.0f, 100, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
          100, 100, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f
    };
    m_program->useToRenderer();
    glClear( GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    GLint params = -1;
    m_program->getActiveUniforms(&params);
    __android_log_print(ANDROID_LOG_INFO, TAG, "getActiveUniforms: %d", params);
    m_program->getActiveUniformMaxLength(&params);
    __android_log_print(ANDROID_LOG_INFO, TAG, "getActiveUniformMaxLength: %d", params);

    glm::mat4  proj = glm::ortho(0.0f, (float)m_width, (float)m_height, 0.0f, 1.0f, -1.0f);
    glUniformMatrix4fv(v_mvp, 1, GL_FALSE, glm::value_ptr(proj));


    glEnableVertexAttribArray(v_position);
    glEnableVertexAttribArray(v_color);
    glVertexAttribPointer(v_position, 4, GL_FLOAT, GL_FALSE, sizeof(float ) *  8, triangle);
    glVertexAttribPointer(v_color, 4, GL_FLOAT, GL_FALSE, sizeof(float ) * 8, &triangle[4]);
    glDrawArrays(GL_TRIANGLES, 0, 3 );
    glDisableVertexAttribArray(v_position);
    glDisableVertexAttribArray(v_color);


    const float triangleA[] = {
            250, 0.0f , 0.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,
            200.0f, 100, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
            300, 100, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f
    };



    glEnableVertexAttribArray(v_position);
    glEnableVertexAttribArray(v_color);
    glVertexAttribPointer(v_position, 4, GL_FLOAT, GL_FALSE, sizeof(float) *  8, triangleA);
    glVertexAttribPointer(v_color, 4, GL_FLOAT, GL_FALSE, sizeof(float ) * 8, &triangleA[4]);
    glDrawArrays(GL_TRIANGLES, 0, 3 );
    glDisableVertexAttribArray(v_position);
    glDisableVertexAttribArray(v_color);


}

