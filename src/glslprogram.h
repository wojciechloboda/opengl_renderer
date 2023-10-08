#pragma once

#include "glad/glad.h"
#include <memory>
#include "shader.h"
#include <vmath.h>
#include <vector>

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
    GLSLProgram();

    void attachVertexShader(const char* path);

    void attachFragmentShader(const char* path);

    void linkProgram();

    void setUniform(const char* name, glm::mat4 matrix);

    void setUniform(const char* name, glm::vec3 vector);

    void setUniform(const char* name, float val);

    void useProgram();
    ~GLSLProgram();

private:
    GLuint programId = 0;
    GLuint vertexShaderId = 0;
    GLuint fragmentShaderId = 0;
    std::unique_ptr<Shader> fragmentShader;
    std::unique_ptr<Shader> vertexShader;
};