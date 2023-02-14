//
// Created by Ych-caihui on 2021/8/17.
//

#include "GLHelloTriangle.h"


const char *vertexShader =  {
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
const char *fragmentShader = {
                "#version 300 es            \n"
                "precision mediump float;   \n"
                "in vec4 f_color;          \n"
                "out vec4 o_color;          \n"
                "void  main()               \n"
                "{                          \n"
                "  o_color = f_color;       \n"
                "}                          \n"
        };


const float triangle[] = {
        50, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 100, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        100, 100, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
};

const float triangleA[] = {
        250, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        200.0f, 100, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        300, 100, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
};


void GLHelloTriangle::onSurfaceCreate() {


    mProgram = ProgramUtils::create(vertexShader, fragmentShader);
    mPositionLoc = glGetAttribLocation(mProgram, "v_position");
    mColorLoc = glGetAttribLocation(mProgram, "v_color");
    mMvpLoc = glGetUniformLocation(mProgram, "v_mvp");

    GLint resultParams = -1;
    glGetProgramiv(mProgram, GL_ACTIVE_UNIFORMS, &resultParams);
    LOG_I(TAG_TEST, "active uniforms: %d", resultParams);

    resultParams = -1;
    glGetProgramiv(mProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &resultParams);
    LOG_I(TAG_TEST, "active uniform max length: %d", resultParams );


}

void GLHelloTriangle::onSurfaceChanged(int width, int height) {
    mWidth = width;
    mHeight = height;
    glViewport(0, 0, width, height);
}


void GLHelloTriangle::onDrawFrame() {

    glUseProgram(mProgram);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glm::mat4 proj = glm::ortho(0.0f, (float) mWidth, (float)mHeight, 0.0f, 1.0f, -1.0f);
    glUniformMatrix4fv(mMvpLoc, 1, GL_FALSE, glm::value_ptr(proj));

    drawTriangle(triangle);
    drawTriangle(triangleA);
}

void GLHelloTriangle::drawTriangle(const float * vertex) const {
    glEnableVertexAttribArray(mPositionLoc);
    glEnableVertexAttribArray(mColorLoc);
    glVertexAttribPointer(mPositionLoc, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8,  vertex);
    glVertexAttribPointer(mColorLoc, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8,  &vertex[4]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(mPositionLoc);
    glDisableVertexAttribArray(mColorLoc);
}

