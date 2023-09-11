
#pragma once 

#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Texture
{
public:
    Texture(const char* path)
    {   
        texture = stbi_load(path, &width, &height, &nrChannels, 0);
        if(!texture)
        {
            fprintf(stderr, "Failed to load\n");
        }

        glGenTextures(1, &textureId);
        if(glGetError() != 0) 
        {
            fprintf(stderr, "Failed to generate texture buffer!\n");
        }

        int err;
        glBindTexture(GL_TEXTURE_2D, textureId);  
        if((err = glGetError()) != 0) 
        {
            fprintf(stderr, "Failed to bind texture!\n");
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
        if(glGetError() != 0) 
        {
            fprintf(stderr, "Failed to pass texture to buffer\n");
        }

        glGenerateMipmap(GL_TEXTURE_2D);
        if(glGetError() != 0) 
        {
            fprintf(stderr, "Failed to generate mipmap\n");
        }

        uniTexture[0] = 200;
        uniTexture[1] = 200;
        uniTexture[2] = 200;
    }

    void load1x1texture()
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, uniTexture);
    }

    void useTexture()
    {
        glBindTexture(GL_TEXTURE_2D, textureId);
    }

    ~Texture()
    {
        stbi_image_free(texture);
    }

private:
    unsigned char *texture;
    GLuint textureId;
    int width, height, nrChannels;

    unsigned char uniTexture[3];
};