
#include <iostream>
#include "glad/glad.h"

#include "GLFW/glfw3.h"
#include "renderer.h"
#include "scene.h"
#include "window.h"

#include "main_window.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "inputHandler.h"
#include "framebuffer.h"
#include "ui.h"


int main()
{
    int width = 1280, height = 720;
    int window_width = 2000, window_height = 1000;
    MainWindow &window = MainWindow::Instance(window_width, window_height);

    Renderer renderer;
    renderer.init();
    Scene scene;
    //scene
    auto sphereTexture = std::make_shared<Texture>("resources/textures/DirtMetal.jpg");
    auto sphereModel = std::make_shared<Model>("resources/meshes/DirtMetal.obj");
    auto cubeModel = std::make_shared<Model>("resources/meshes/cube.obj");
    Object sphere1(sphereModel);
    Object sphere2(sphereModel);
    sphere1.loadTexture(sphereTexture);
    sphere2.loadTexture(sphereTexture);
    scene.objects.push_back(sphere1);
    scene.objects.push_back(sphere2);

    scene.mainCamera = glm::vec3(0.0, 0.0, -1.0);
    scene.pointLightPosition = glm::vec3(0.7f, 0.0f, 0.0f);

    window.setScene(&scene);
    
    Framebuffer framebuffer(width, height);
    UI ui;

    double currentFrame, lastFrame = glfwGetTime(), deltaTime;

    while(!window.shouldClose())
    {
        framebuffer.bind();

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window.processInput(deltaTime);
        renderer.render(&scene, width, height);

        ui.renderFrame(scene, framebuffer, width, height, 
            window_width, window_height, window);

        window.swapBuffers();
        glfwPollEvents();    
    }

    return 0;   
}