
#pragma once

class Framebuffer
{
public:
    Framebuffer(int width, int height)
    {
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        glGenTextures(1, &color_texture);
        glBindTexture(GL_TEXTURE_2D, color_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGenTextures(1, &depth_stencil_texture);
        glBindTexture(GL_TEXTURE_2D, depth_stencil_texture);
        glTexImage2D(
                GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, 
                GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

        glFramebufferTexture(GL_FRAMEBUFFER,
                         GL_COLOR_ATTACHMENT0,
                         color_texture, 0);

        glFramebufferTexture(GL_FRAMEBUFFER,
                         GL_DEPTH_STENCIL_ATTACHMENT,
                         depth_stencil_texture, 0);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }

    void bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    }

    GLuint getColorTexture() const
    {
        return color_texture;
    }

    ~Framebuffer()
    {
        glDeleteBuffers(1, &fbo);
        glDeleteTextures(1, &color_texture);
        glDeleteTextures(1, &depth_stencil_texture);
    }

private:
    GLuint fbo;
    GLuint color_texture;
    GLuint depth_stencil_texture;
};


