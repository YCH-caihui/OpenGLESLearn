//
// Created by Ych-caihui on 2022/2/17.
//

#ifndef ALONEGLESLEARN_GLYUVMAP_H
#define ALONEGLESLEARN_GLYUVMAP_H

#include "GLRenderer.h"
#include "GLProgram.h"
#include "NativeImage.h"


struct YUVRect {
    glm::vec4 position;
    glm::vec2 texCoordinate;
};

class GLYuvMap : public GLRenderer
{

private:
    const char * vs = {
            "#version 300 es           \n"
            "layout(location = 0) in vec4 a_position;   \n"
            "layout(location = 1) in vec2 a_texCoordinate;  \n"
            "out vec2 v_texCoordinate;                       \n"
            "void main()                                     \n"
            "{                                               \n"
            "   gl_Position = a_position;                   \n"
            "   v_texCoordinate  = a_texCoordinate;         \n"
            "}                                              \n"
    };

    const char * fs = {
            "#version 300 es                              \n"
            "precision mediump float;                     \n"
            "in vec2 v_texCoordinate;                     \n"
            "layout(location = 0) out vec4 outColor;      \n"
            "uniform sampler2D y_texture;                 \n"
            "uniform sampler2D uv_texture;                \n"
            "void main()                                  \n"
            "{                                            \n"
            "   vec3 yuv;                                 \n"
            "  yuv.x = texture(y_texture, v_texCoordinate).r;  \n"
            "  yuv.y = texture(uv_texture, v_texCoordinate).r - 0.5; \n"
            "  yuv.z = texture(uv_texture, v_texCoordinate).a - 0.5; \n"
            " highp vec3 rgb = mat3(    1, 1, 1,                   \n"
            "                          0, -0.344, 1.770,          \n"
            "                          1.403, -0.714, 0) * yuv;    \n"
            " outColor = vec4(rgb, 1);                            \n"
            "}                                                    \n"

    };

    YUVRect * mRect;
    GLProgram * mProgram;
    attribute mPositionIndex;
    attribute mTexCoordinateIndex;
    uniform mYTextureIndex;
    uniform mUvTextureIndex;
    GLuint *mTextureId = new GLuint[2];



public:

    GLYuvMap()
    {

        mRect = new YUVRect[] {
                glm::vec4(-1.0f,  0.78f, 0.0f, 1.0f),   glm::vec2(0.0f, 0.0f),
                glm::vec4(-1.0f, -0.78f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f),
                glm::vec4(1.0f,  -0.78f, 0.0f, 1.0f),  glm::vec2(1.0f, 1.0f),
                glm::vec4(1.0f,   0.78f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f),
        };
    }

    void onSurfaceCreate() override;
    void onSurfaceChanged(int width, int height) override;
    void onDrawFrame() override;
    void initNativeImage() override;
    ~GLYuvMap() {
        if(mTextureId != NULL) {
            delete[] mTextureId;
        }
    }
};

#endif //ALONEGLESLEARN_GLYUVMAP_H
