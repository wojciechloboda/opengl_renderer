
#include <iostream>
#include "glad/glad.h"

#include "GLFW/glfw3.h"
#include "renderer.h"
#include "scene.h"

Renderer renderer;
double lastX, lastY, yaw = 0.0, pitch = 0.0;
vmath::vec3 cameraFront;
bool firstMouse;

void window_size_callback(GLFWwindow* window, int width, int height)
{
    renderer.onResize(width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    vmath::vec3 direction;
    direction[0] = cos(vmath::radians(yaw)) * cos(vmath::radians(pitch));
    direction[1] = sin(vmath::radians(pitch));
    direction[2] = sin(vmath::radians(yaw)) * cos(vmath::radians(pitch));
    cameraFront = vmath::normalize(direction);
}  

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window, Scene *scene, double deltaTime)
{
    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        scene->mainCamera.position += cameraSpeed * scene->mainCamera.cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        scene->mainCamera.position -= cameraSpeed * scene->mainCamera.cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        scene->mainCamera.position -= vmath::normalize(
            vmath::cross(scene->mainCamera.cameraFront, scene->mainCamera.upDirection)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        scene->mainCamera.position += vmath::normalize(
            vmath::cross(scene->mainCamera.cameraFront, scene->mainCamera.upDirection)) * cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

int main()
{
    if(!glfwInit())
    {
        fprintf(stderr, "Failed to init GLFW\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int height = 1280, width = 720;
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Renderer", NULL, NULL);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 

    if (window == NULL)
    {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return 1;
    }  

    
    glViewport(0, 0, height, width);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(window, mouse_callback);  
    glfwSetWindowSizeCallback(window, window_size_callback);

    //Renderer renderer;
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

    double currentFrame, lastFrame = glfwGetTime(), deltaTime;

    while(!glfwWindowShouldClose(window))
    {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, &scene, deltaTime);
        scene.mainCamera.cameraFront = cameraFront;
        renderer.render(&scene);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwTerminate();
    return 0;   
}