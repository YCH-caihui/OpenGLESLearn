//
// Created by Ych-caihui on 2021/8/17.
//
#include "GLProgram.h"


GLProgram::GLProgram(const GLchar * vertexShaderSource, const GLchar * fragmentShaderSource)
{
    GLint resultParam = -1;
    GLuint vertexShaderId = -1;
    GLuint fragmentShaderId = -1;

    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShaderId);
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &resultParam);
    if(resultParam != GL_TRUE)
    {
        glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &resultParam);
        auto * infoLog = new GLchar[resultParam + 1];
        glGetShaderInfoLog(vertexShaderId, resultParam, nullptr, infoLog);
        __android_log_print(ANDROID_LOG_ERROR, TAG_TEST, "Failed to compile vertex shader: %s", infoLog);
        glDeleteShader(vertexShaderId);
        delete[] infoLog;
        return;
    }

    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShaderId);
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &resultParam);
    if(resultParam != GL_TRUE)
    {
        glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &resultParam);
        auto * infoLog = new GLchar[resultParam + 1];
        glGetShaderInfoLog(fragmentShaderId, resultParam, nullptr, infoLog);
        __android_log_print(ANDROID_LOG_ERROR, TAG_TEST, "Failed to compile fragment shader: %s", infoLog);
        glDeleteShader(fragmentShaderId);
        delete[] infoLog;
        return;
    }

    m_programId = glCreateProgram();
    glAttachShader(m_programId, vertexShaderId);
    glAttachShader(m_programId, fragmentShaderId);
    glLinkProgram(m_programId);
    glGetProgramiv(m_programId, GL_LINK_STATUS, &resultParam);
    if(resultParam != GL_TRUE)
    {
        glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &resultParam);
        auto * infoLog = new GLchar[resultParam + 1];
        glGetProgramInfoLog(m_programId, resultParam, 0, infoLog);
        __android_log_print(ANDROID_LOG_ERROR, TAG_TEST, "Failed to lint program: %s", infoLog);
        glDeleteProgram(m_programId);
        delete[] infoLog;
        return;
    }

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
}

GLuint GLProgram::glGetUniformBlockIndex(const GLchar *uniformBlockName)
{
   return ::glGetUniformBlockIndex(m_programId, uniformBlockName);
}

void GLProgram::glUniformBlockBinding(GLuint blockIndex, GLuint uBlockBinding)
{
    return ::glUniformBlockBinding(m_programId, blockIndex, uBlockBinding);
}

void GLProgram::useToRenderer()
{
    glUseProgram(m_programId);
}

GLuint GLProgram::getAttribLocation(const GLchar *name)
{
    return glGetAttribLocation(m_programId, name);
}

GLuint GLProgram::getUniformLocation(const char *name)
{
    return glGetUniformLocation(m_programId, name);
}


void  GLProgram::getActiveUniforms(GLint * params)
{
    glGetProgramiv(m_programId, GL_ACTIVE_UNIFORMS, params );
}

void GLProgram::getActiveUniformMaxLength(GLint * params)
{
    glGetProgramiv(m_programId, GL_ACTIVE_UNIFORM_MAX_LENGTH, params);
}

GLProgram::~GLProgram()
{
    glDeleteProgram(m_programId);
}