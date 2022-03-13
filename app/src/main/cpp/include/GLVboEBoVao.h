//
// Created by Ych-caihui on 2022/3/12.
//

#ifndef ALONEGLESLEARN_GLVBOEBOVAO_H
#define ALONEGLESLEARN_GLVBOEBOVAO_H

#include "GLRenderer.h"
#include "GLProgram.h"
#include "NativeImage.h"

struct VBORect {
    glm::vec4 position;
    glm::vec2  texCoordinate;
};

class GLYboEBoVao : public GLRenderer
{
private:
    const char * vs = {
            "#version 300 es   \n"
            "layout(location = 0) in vec4 a_position;    \n"
            "layout(location = 1) in vec2 a_texCoordinate; \n"
            "out vec2 v_texCoordinate;                    \n"
            "void main()                                 \n"
            "{                                           \n"
            "   gl_Position = a_position;                \n"
            "   v_texCoordinate = a_texCoordinate;       \n"
            "}                                           \n"
    };

    const char * fs = {
            "#version 300 es                             \n"
            "precision mediump float;                    \n"
            "in vec2 v_texCoordinate;                    \n"
            "uniform sampler2D s_textureMap;            \n"
            "layout(location = 0) out vec4 outColor;    \n"
            "void main()                               \n"
            "{                                         \n"
            " outColor =texture(s_textureMap, v_texCoordinate);  \n"
            "}                                                \n"

    };

    VBORect * mRect;
    GLProgram * mProgram;
    attribute mPositionIndex;
    attribute  mTexCoordinateIndex;
    attribute  mTextureIndex;
    GLuint mTextureId;

    GLuint mVaoId;

    GLuint mVboIds[2];
    GLushort mIndices[6]  = {0, 1, 2, 0, 2, 3};


public:

    GLYboEBoVao()
    {
        mRect = new VBORect[] {
                glm::vec4(-1.0f, 1.0f, 0.0f, 1.0f),   glm::vec2(0.0f, 0.0f),
                glm::vec4(-1.0f, -1.0f , 0.0f , 1.0f), glm::vec2(0.0f, 1.0f),
                glm::vec4(1.0f, -1.0f,  0.0f, 1.0f), glm::vec2(1.0f, 1.0f),
                glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 0.0f)



        };

    }

    void onSurfaceCreate() override;
    void onSurfaceChanged(int width, int height) override;
    void onDrawFrame() override;

    void initNativeImage() override;

    ~GLYboEBoVao()
    {
        if(mRect != nullptr)
        {
            delete[] mRect;
            mRect = nullptr;
        }
    }

};


#endif //ALONEGLESLEARN_GLVBOEBOVAO_H
