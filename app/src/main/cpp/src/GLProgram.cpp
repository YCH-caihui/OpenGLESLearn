//
// Created by 杨财辉 on 3/11/21.
//
#include "GLShader.h"


GLProgram::GLProgram() {
    m_programId = -1;
    createProgram(getVertexShader(), getFragmentShader());
}


bool GLProgram::createProgram(const char *vertex, const char *fragment) {
    bool isSucceed = false;
    if (vertex) {
        m_vertex.m_shaderId = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(m_vertex.m_shaderId, 1, &vertex, nullptr);
        glCompileShader(m_vertex.m_shaderId);

        GLint compileStatus;
        glGetShaderiv(m_vertex.m_shaderId, GL_COMPILE_STATUS, &compileStatus);
        isSucceed = compileStatus == GL_TRUE;
        if (!isSucceed) {
            GLint buffLength;
            glGetShaderiv(m_vertex.m_shaderId, GL_INFO_LOG_LENGTH, &buffLength);
            char message[buffLength];
            glGetShaderInfoLog(m_vertex.m_shaderId, sizeof(message), nullptr, message);
            __android_log_print(ANDROID_LOG_ERROR, TAG, "<createProgram>  error info: %s", message);

            goto error;
        }
    }
    if (fragment) {
        m_fragment.m_shaderId = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(m_fragment.m_shaderId, 1, &fragment, nullptr);
        glCompileShader(m_fragment.m_shaderId);


        GLint compileState;
        glGetShaderiv(m_fragment.m_shaderId, GL_COMPILE_STATUS, &compileState);
        isSucceed = compileState == GL_TRUE;
        if (!isSucceed) {
            GLint buffLength;
            glGetShaderiv(m_fragment.m_shaderId, GL_INFO_LOG_LENGTH, &buffLength);
            char message[buffLength];
            glGetShaderInfoLog(m_fragment.m_shaderId, size_t(message), nullptr, message);
            __android_log_print(ANDROID_LOG_ERROR, TAG, "<createProgram> error info: %s", message);
            goto error;
        }
    }

    m_programId = glCreateProgram();

    if (m_vertex.m_shaderId) {
        glAttachShader(m_programId, m_vertex.m_shaderId);
    }

    if (m_fragment.m_shaderId) {
        glAttachShader(m_programId, m_fragment.m_shaderId);
    }

    glLinkProgram(m_programId);

    GLint linkStatus;
    glGetProgramiv(m_programId, GL_LINK_STATUS, &linkStatus);
    isSucceed = linkStatus == GL_TRUE;
    if (!isSucceed) {
        GLint bufLength;
        glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &bufLength);
        char message[bufLength];
        glGetProgramInfoLog(m_programId, sizeof(message), nullptr, message);
        __android_log_print(ANDROID_LOG_ERROR, TAG, "<createProgram>  error info: %s", message);
        goto error;
    }


    return isSucceed;
    error:
    if (m_vertex.m_shaderId) {
        glDeleteShader(m_vertex.m_shaderId);
    }
    if (m_fragment.m_shaderId) {
        glDeleteShader(m_fragment.m_shaderId);

        if (m_programId) {
            glDeleteProgram(m_programId);
        }

        return isSucceed;
    }

}


void GLProgram::dispatchDraw() {
    begin();onDraw();end();
}

void GLProgram::begin() {
    glUseProgram(m_programId);
}

void GLProgram::onDraw() {

}


void GLProgram::end() {
    glUseProgram(0);
}

