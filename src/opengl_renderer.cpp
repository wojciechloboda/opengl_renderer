
#include <iostream>
#include "glad/glad.h"

#include "GLFW/glfw3.h"
#include "renderer.h"
#include "scene.h"
#include "window.h"


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
    //GLFW::Window window(height, width);

    GLFW::Window window(window_width, window_height);
    window.makeContextCurrent();
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return 1;
    }  
    glViewport(0, 0, width, height);


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
    //

    InputHandler inputHandler(window, scene);

    // Setup Dear ImGui context
    const char* glsl_version = "#version 130";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window.get(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    
    Framebuffer framebuffer(width, height);
    UI ui;

    double currentFrame, lastFrame = glfwGetTime(), deltaTime;
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();

    ///////////////////////////////////

    while(!window.shouldClose())
    {
        framebuffer.bind();

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        inputHandler.processInput(deltaTime);
        renderer.render(&scene, width, height);


        ui.renderFrame(scene, framebuffer, width, height, 
            window_width, window_height, window, inputHandler);

        window.swapBuffers();
        glfwPollEvents();    
    }

    return 0;   
}