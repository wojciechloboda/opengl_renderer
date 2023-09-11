#pragma once

#include "glad/glad.h"
#include <vmath.h>

class Camera 
{
public:
    vmath::vec3 position;
    vmath::vec3 cameraFront;
    vmath::vec3 upDirection;

    float yaw;
    float pitch;

    Camera(vmath::vec3 pos)
        : position{pos}, 
          cameraFront{vmath::vec3(0.0, 0.0, 1.0)},
          upDirection{vmath::vec3(0.0, 1.0, 0.0)} {}
private:
};