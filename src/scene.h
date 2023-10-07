
#pragma once

#include <vmath.h>
#include "object.h"
#include "camera.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

class Scene 
{
public:
    std::vector<Object> objects;
    Camera mainCamera;
    glm::vec3 pointLightPosition;

    Scene() : mainCamera(glm::vec3(0.0, 0.0, 0.0)) {}
private:

};

