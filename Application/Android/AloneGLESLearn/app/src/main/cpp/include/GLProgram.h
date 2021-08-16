//
// Created by Ych-caihui on 2021/8/17.
//

#ifndef ALONEGLESLEARN_GLPROGRAM_H
#define ALONEGLESLEARN_GLPROGRAM_H
#include <GLES3//gl3.h>
#include <android/log.h>

#define TAG "YCH/GLProgram"

typedef GLint attribute;
typedef GLint uniform;

class GLProgram
{
private:
    int m_programId = -1;

public:
    GLProgram(const GLchar * vertexShaderSource, const GLchar * fragmentShaderSource);

    void useToRenderer();

    attribute getAttribLocation(const GLchar * name);

    uniform  glUniformLocation(const char * name);

    ~GLProgram();
};

#endif //ALONEGLESLEARN_GLPROGRAM_H
