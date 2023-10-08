
#pragma once

#include "glad/glad.h"

class Framebuffer
{
public:
    Framebuffer(int width, int height);
    void bind();
    GLuint getColorTexture() const;
    ~Framebuffer();
private:
    GLuint fbo;
    GLuint color_texture;
    GLuint depth_stencil_texture;
};


