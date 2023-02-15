//
// Created by Ych-caihui on 2021/8/17.
//
#include "GLProgram.h"


#define TAG "YCH/GLProgram"

 GLuint ProgramUtils::create(const GLchar * vShader, const GLchar * fShader) {
    auto vShaderId = buildShader(GL_VERTEX_SHADER, vShader);
    auto fShaderId = buildShader(GL_FRAGMENT_SHADER, fShader);
    if(vShaderId == -1 || fShaderId == -1) return -1;
    GLuint  programId  = glCreateProgram();
    glAttachShader(programId, vShaderId);
    glAttachShader(programId, fShaderId);
    glLinkProgram(programId);

    GLint  resultParam = -1;
    glGetProgramiv(programId, GL_LINK_STATUS, &resultParam);
    if(resultParam != GL_TRUE) {
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &resultParam);
        auto * infoLog = new GLchar[resultParam + 1];
        glGetProgramInfoLog(programId, resultParam, 0, infoLog);
        LOG_E(TAG, "Failed to lint program: %s", infoLog);
        glDeleteProgram(programId);
        delete [] infoLog;
        return -1;
    }
    return programId;
}


 GLuint ProgramUtils::buildShader(GLenum shaderType, const GLchar * shaderSource) {
    GLuint shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &shaderSource, nullptr);
    glCompileShader(shaderId);
    GLint  compileStates = -1;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStates);
    if(compileStates  != GL_TRUE) {
        GLint infoLogLength  = -1;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        auto  * infoLog = new GLchar [infoLogLength + 1];
        glGetShaderInfoLog(shaderId, infoLogLength, nullptr, infoLog);
        LOG_E(TAG, "Failed to compile  %s  shader: %s", shaderType == GL_VERTEX_SHADER ? "vertex_shader" : "fragment_shader" , infoLog);
        glDeleteShader(shaderId);
        delete[] infoLog;
        return -1;
    }

    return shaderId;
}

