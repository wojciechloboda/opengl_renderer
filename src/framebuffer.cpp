
#include "framebuffer.h"
#include "glad/glad.h"
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

Framebuffer::Framebuffer(int width, int height)
{
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &this->color_texture);
    glBindTexture(GL_TEXTURE_2D, this->color_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenTextures(1, &this->depth_stencil_texture);
    glBindTexture(GL_TEXTURE_2D, this->depth_stencil_texture);
    glTexImage2D(
            GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, 
            GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

    glFramebufferTexture(GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            this->color_texture, 0);

    glFramebufferTexture(GL_FRAMEBUFFER,
            GL_DEPTH_STENCIL_ATTACHMENT,
            this->depth_stencil_texture, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	    std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
}

void Framebuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
}

GLuint Framebuffer::getColorTexture() const
{
    return this->color_texture;
}

Framebuffer::~Framebuffer()
{
    glDeleteBuffers(1, &this->fbo);
    glDeleteTextures(1, &this->color_texture);
    glDeleteTextures(1, &this->depth_stencil_texture);
}

