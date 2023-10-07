#pragma once

#include "glad/glad.h"
#include <memory>
#include "shader.h"
#include <vmath.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <glm/gtc/type_ptr.hpp>

class GLSLProgram
{
public:
    GLSLProgram()
    {
        programId = glCreateProgram();
        if(glGetError() != 0)
        {
            fprintf(stderr,"Error creating a program\n");
        }
    }

    void attachVertexShader(const char* path)
    {
        vertexShader = std::make_unique<Shader>(path, GL_VERTEX_SHADER);
        glAttachShader(programId, vertexShader->shaderId);
        if(glGetError() != 0)
        {
            fprintf(stderr, "Error attaching a shader to a program\n");
        }
    }

    void attachFragmentShader(const char* path)
    {
        fragmentShader = std::make_unique<Shader>(path, GL_FRAGMENT_SHADER);
        glAttachShader(programId, fragmentShader->shaderId);
        if(glGetError() != 0)
        {
            fprintf(stderr, "Error attaching a shader to a program\n");
        }
    }

    void linkProgram()
    {
        glLinkProgram(programId);
        if(glGetError() != 0)
        {
            fprintf(stderr, "Error linking a program\n");
        }
    }

    void setUniform(const char* name, glm::mat4 matrix)
    {
        GLuint location = glGetUniformLocation(programId, name);
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
        if(glGetError() != 0)
        {
            fprintf(stderr, "Error setting uniform\n");
        }
    }

    void setUniform(const char* name, glm::vec3 vector)
    {
        GLuint location = glGetUniformLocation(programId, name);
        glUniform3fv(location, 1, glm::value_ptr(vector));
        if(glGetError() != 0)
        {
            fprintf(stderr, "Error setting uniform\n");
        }
    }

    void setUniform(const char* name, float val)
    {
        GLuint location = glGetUniformLocation(programId, name);
        glUniform1fv(location, 1, &val);
        if(glGetError() != 0)
        {
            fprintf(stderr, "Error setting uniform\n");
        }
    }

    void useProgram()
    {
        glUseProgram(programId);
    }

    ~GLSLProgram()
    {
        glDeleteProgram(programId);
    }

private:
    GLuint programId = 0;
    GLuint vertexShaderId = 0;
    GLuint fragmentShaderId = 0;
    std::unique_ptr<Shader> fragmentShader;
    std::unique_ptr<Shader> vertexShader;
};