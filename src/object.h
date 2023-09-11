#pragma once

#include <vmath.h>
#include "texture.h"
#include "model.h"
#include "glad/glad.h"

class Object
{
public:
    std::shared_ptr<Model> model;
    vmath::vec3 position{0.0f, 0.0f, 0.0f};
    vmath::vec3 scale{1.0f, 1.0f, 1.0f};
    vmath::vec3 diffuse;
    vmath::vec3 ambient;
    vmath::vec3 specular;
    float shininess = 32.0f;

    Object(std::shared_ptr<Model> initModel)
        : position(0.0f, 0.0f, 0.0f), 
          scale(1.0f, 1.0f, 1.0f),
          ambient(0.1f, 0.1f, 0.1f),
          diffuse(0.5f, 0.5f, 0.31f),
          specular(0.5f, 0.5f, 0.5f),
          model(initModel) {}

    void loadTexture(std::shared_ptr<Texture> texture)
    {
        is_texture_loaded = true;
        objectTexture = texture;
    }

    void draw() const
    {
        if(is_texture_loaded)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            objectTexture->useTexture();
        }

        model->drawModel();
    }

private:
    std::shared_ptr<Texture> objectTexture;
    bool is_texture_loaded = false;
};