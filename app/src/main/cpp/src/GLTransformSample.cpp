//
// Created by chyan on 2023/2/17.
//

#include "GLTransformSample.h"


namespace GLTransformShader {
    const GLchar *vs = {
            "#version 300 es                           \n"
            "layout(location = 0) in vec4 a_position;  \n"
            "layout(location = 1) in vec2 a_texCoordinate; \n"
            "out vec2 v_texCoordinate;                     \n"
            "void main()                                   \n"
            "{                                             \n"
            "    gl_Position = a_position;                 \n"
            "    v_texCoordinate = a_texCoordinate;        \n"
            "}                                            \n"
    };


    const GLchar *fs = {
            "#version 300 es                               \n"
            "precision mediump float;                      \n"
            "in vec2 v_texCoordinate;                      \n"
            "uniform sampler2D s_TextureMap;               \n"
            "layout(location = 0) out vec4 outColor;       \n"
            "void main()                                   \n"
            "{                                              \n"
            "   outColor = texture(s_TextureMap, v_texCoordinate); \n"
            "}                                                    \n"
    };




}



GLTransformSample::GLTransformSample() {

}


void GLTransformSample::onSurfaceCreate() {
    mProgramId = ProgramUtils::create(GLTransformShader::vs, GLTransformShader::fs);
    mPositionLoc = glGetAttribLocation(mProgramId, "a_position");
    mTexCoordinateLoc = glGetAttribLocation(mProgramId, "a_texCoordinate");
    mTextureLoc = glGetAttribLocation(mProgramId, "s_TextureMap");


}

void GLTransformSample::onSurfaceChanged(int width, int height) {

}


void GLTransformSample::updateParameter(JNIEnv * env, int paramType, jobject paramObj) {

}

void GLTransformSample::onDrawFrame() {

}



GLTransformSample::~GLTransformSample() {

}