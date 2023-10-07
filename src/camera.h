#pragma once

#include "glad/glad.h"
#include <vmath.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

class Camera 
{
public:
    glm::vec3 position;
    glm::vec3 cameraFront;
    glm::vec3 upDirection;

    float yaw;
    float pitch;

    Camera(glm::vec3 pos)
        : position{pos}, 
          cameraFront{glm::vec3(0.0, 0.0, 1.0)},
          upDirection{glm::vec3(0.0, 1.0, 0.0)} {}
private:
};