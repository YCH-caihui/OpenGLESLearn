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
typedef GLuint * bufferId;
typedef GLuint * textureId;

class GLProgram
{
private:
    int m_programId = -1;

public:
    GLProgram(const GLchar * vertexShaderSource, const GLchar * fragmentShaderSource);

    void useToRenderer();

    attribute getAttribLocation(const GLchar * name);

    uniform  getUniformLocation(const char * name);

    void  getActiveUniforms(GLint * params);

    GLuint  glGetUniformBlockIndex(const GLchar * uniformBlockName);
    void glUniformBlockBinding(GLuint blockIndex, GLuint uBlockBinding);

    void getActiveUniformMaxLength(GLint * params);

    ~GLProgram();
};

#endif //ALONEGLESLEARN_GLPROGRAM_H
