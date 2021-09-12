//
// Created by Ych-caihui on 2021/9/2.
//
#include "GLTexture.h"


void GLTexture::onSurfaceCreate()
{
    const char * vs =
     {
            "#version 300 es             \n"
            "layout(std140) uniform MatrixBlock \n"
            "{                                   \n"
            "  mat4 projection;                  \n "
            "} matrices;                          \n"
            "in vec4 v_position;                 \n"
            "in vec2 v_texCoord;                 \n"
            "out vec2 f_texCoord;                \n"
            "void main()                         \n"
            "{                                   \n"
            "   gl_Position = matrices.projection * v_position;        \n"
            "   f_texCoord = v_texCoord;         \n"
            "}                                   \n"
    };

    const char * fs =
    {
            "#version 300 es                 \n"
            "precision mediump float;         \n"
            "in vec2 f_texCoord;              \n"
            "out vec4 out_color;              \n"
            "//RGB 的变换因子，即权重值            \n"
            "const highp vec3  W = vec3(0.2125, 0.7154, 0.0721);      \n"
            "uniform sampler2D f_texture;     \n"
            "void main()                      \n"
            "{                                \n"
            "//获取对应纹理坐标系下颜色值  \n"
            "  vec4 mask = texture(f_texture, f_texCoord);  \n"
            "//将颜色mask 与变换因子想乘得到灰度值                \n"
            "float luminance = dot(mask.rgb, W);             \n"
            "//将灰度转换为（luminance, luminance, luminance.mask.a）并填充到像素中  \n"
            "out_color    = vec4(vec3(luminance), 1.0f);          \n"

            "}                                \n"
    };

    m_program = new GLProgram(vs, fs);
    v_position = m_program->getAttribLocation("v_position");
    v_texCoord = m_program->getAttribLocation("v_texCoord");
    f_texture = m_program->getUniformLocation("f_texture");

    m_textureIds = new GLuint[1]();
    glGenTextures(1, m_textureIds);
    glBindTexture(GL_TEXTURE_2D, m_textureIds[0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,GL_NONE);



}


void GLTexture::onSurfaceChanged(int width, int height)
{
    m_width = width;
    m_height = height;
    m_program->useToRenderer();
    glm::mat4  proj = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 1.0f, -1.0f);
    int blockIndex = m_program->glGetUniformBlockIndex("MatrixBlock");
    GLuint blockPoint = 0;
    m_program->glUniformBlockBinding(blockIndex, blockPoint);
    m_uniform_bufferId = new GLuint[1];
    glGenBuffers(1, m_uniform_bufferId);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uniform_bufferId[0]);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), glm::value_ptr(proj), GL_DYNAMIC_READ);
    glBindBufferBase(GL_UNIFORM_BUFFER, blockPoint, m_uniform_bufferId[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void GLTexture::setBitmap(XBitmap *bitmap) {
    __android_log_print(ANDROID_LOG_DEBUG, "ccc",  "===width:%d  height:%d format :%d" ,bitmap->info->width, bitmap->info->height, bitmap->info->format);
    glBindTexture(GL_TEXTURE_2D, m_textureIds[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap->info->width, bitmap->info->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap->addrPtr);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);
}

void GLTexture::onDrawFrame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0f, 1.0f, 1.0f);


    Vertex  vertex[] =
     {

            glm::vec4(0.0f,  m_height, 0.0f, 1.0f), glm::vec2(0.0f , 1.0f),
            glm::vec4(m_width, m_height, 0.0f , 1.0f), glm::vec2(1.0f, 1.0f),
            glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f),
            glm::vec4(m_width, 0.0f, 0.0f , 1.0f), glm::vec2(1.0, 0.0f)
     };

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureIds[0]);
    glUniform1i(GL_TEXTURE_2D, m_textureIds[0]);


    glEnableVertexAttribArray(v_position);
    glEnableVertexAttribArray(v_texCoord);
    glVertexAttribPointer(v_position, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), vertex);
    glVertexAttribPointer(v_texCoord, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), &vertex[0].coord);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableVertexAttribArray(v_texCoord);
    glDisableVertexAttribArray(v_position);


}