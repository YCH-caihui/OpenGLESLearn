//
// Created by Ych-caihui on 2021/8/17.
//

#ifndef ALONEGLESLEARN_GLPROGRAM_H
#define ALONEGLESLEARN_GLPROGRAM_H
#include <GLES3//gl3.h>
#include <android/log.h>




#define  LOG_E(T, ...)  __android_log_print(ANDROID_LOG_ERROR,T,__VA_ARGS__)
#define  LOG_I(T, ...)  __android_log_print(ANDROID_LOG_INFO, T, __VA_ARGS__)
#define  LOG_D(T, ...) __android_log_print(ANDROID_LOG_DEBUG, T, __VA_ARGS__)



class ProgramUtils {

public:
    static GLuint create(const GLchar * vShader, const GLchar * fShader);
private:
    static GLuint buildShader(GLenum shaderType, const GLchar * shaderSource);

};



#endif //ALONEGLESLEARN_GLPROGRAM_H
