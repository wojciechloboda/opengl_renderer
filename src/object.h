#pragma once

#include <vmath.h>
#include "texture.h"
#include "model.h"
#include "glad/glad.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4

class Object
{
public:
    std::shared_ptr<Model> model;
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec3 scale{1.0f, 1.0f, 1.0f};
    glm::vec3 diffuse;
    glm::vec3 ambient;
    glm::vec3 specular;
    float shininess = 32.0f;
    std::string name;

    float position_arr[3];
    float scale_arr[3];

    Object(std::shared_ptr<Model> initModel)
        : position(0.0f, 0.0f, 0.0f), 
          position_arr{0.0f, 0.0f, 0.0f},
          scale(1.0f, 1.0f, 1.0f),
          scale_arr{1.0f, 1.0f, 1.0f},
          ambient(0.1f, 0.1f, 0.1f),
          diffuse(0.5f, 0.5f, 0.31f),
          specular(0.5f, 0.5f, 0.5f),
          model(initModel),
          name("def") {}

    void loadTexture(std::shared_ptr<Texture> texture)
    {
        is_texture_loaded = true;
        objectTexture = texture;
    }

    void draw() 
    {
        //temporary
        position = glm::vec3(position_arr[0], position_arr[1], position_arr[2]);
        scale = glm::vec3(scale_arr[0], scale_arr[1], scale_arr[2]);
        //

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