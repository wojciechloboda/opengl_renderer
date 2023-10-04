
#include <iostream>
#include "glad/glad.h"

#include "GLFW/glfw3.h"
#include "renderer.h"
#include "scene.h"
#include "window.h"
#include "inputHandler.h"

int main()
{
    int height = 1280, width = 720;
    GLFW::Window window(height, width);
    window.makeContextCurrent();
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return 1;
    }  
    glViewport(0, 0, height, width);

    Renderer renderer;
    renderer.init();
    Scene scene;
    //scene
    auto sphereTexture = std::make_shared<Texture>("resources/textures/DirtMetal.jpg");
    auto sphereModel = std::make_shared<Model>("resources/meshes/DirtMetal.obj");
    auto cubeModel = std::make_shared<Model>("resources/meshes/cube.obj");
    Object sphere1(sphereModel);
    Object sphere2(sphereModel);
    sphere1.position = vmath::vec3(-0.3f, -0.0f, 0.0f);
    sphere1.scale = vmath::vec3(0.01f, 0.01f, 0.01f);
    sphere1.loadTexture(sphereTexture);
    sphere2.position = vmath::vec3(1.3f, -0.0f, 0.0f);
    sphere2.scale = vmath::vec3(0.01f, 0.01f, 0.01f);
    sphere2.loadTexture(sphereTexture);
    scene.objects.push_back(sphere1);
    scene.objects.push_back(sphere2);

    scene.mainCamera = vmath::vec3(0.0, 0.0, -1.0);
    scene.pointLightPosition = vmath::vec3(0.7f, 0.0f, 0.0f);
    //

    InputHandler inputHandler(window, renderer, scene);


    double currentFrame, lastFrame = glfwGetTime(), deltaTime;
    while(!window.shouldClose())
    {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        inputHandler.processInput(deltaTime);
        renderer.render(&scene);

        window.swapBuffers();
        glfwPollEvents();    
    }

    return 0;   
}