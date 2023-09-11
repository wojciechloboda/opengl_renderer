
#pragma once

#include <vmath.h>
#include "object.h"
#include "camera.h"

class Scene 
{
public:
    std::vector<Object> objects;
    Camera mainCamera;
    vmath::vec3 pointLightPosition;

    Scene() : mainCamera(vmath::vec3(0.0, 0.0, 0.0)) {}
private:

};

