#pragma once

#include "GLFW/glfw3.h"
#include "renderer.h"


namespace GLFW
{
    
class Window
{
public:
    Window(int height, int width)
    {
        if(!glfwInit())
        {
            fprintf(stderr, "Failed to init GLFW\n");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(height, width, "Renderer", NULL, NULL);

        if (window == NULL)
        {
            fprintf(stderr, "Failed to create GLFW window\n");
        }

        glfwSetInputMode(window, GLFW_CURSOR,  GLFW_CURSOR_DISABLED);
    }

    void makeContextCurrent()
    {
        glfwMakeContextCurrent(window);
    }

    int getKey(int key)
    {
        return glfwGetKey(window, key);
    }

    ~Window()
    {
        glfwTerminate();
    }

    void setWindowSizeCallback(GLFWwindowsizefun cbfun)
    {
        glfwSetWindowSizeCallback(window, cbfun);
    }

    void setCursorPosCallback(GLFWcursorposfun cbfun)
    {
        glfwSetCursorPosCallback(window, cbfun); 
    }

    void setFramebufferSizeCallback(GLFWframebuffersizefun framebuffer_size_callback)
    {
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    }

    bool shouldClose()
    {
        return glfwWindowShouldClose(window);
    }

    void swapBuffers()
    {
        glfwSwapBuffers(window);
    }

    void* getUserPointer()
    {
        return glfwGetWindowUserPointer(window);
    }

    void setUserPointer(void *pointer)
    {
        return glfwSetWindowUserPointer(window, pointer);
    }

    void setShouldClose()
    {
        glfwSetWindowShouldClose(window, true);
    }

private:
    GLFWwindow* window;
    double lastX, lastY, yaw = 0.0, pitch = 0.0;
    vmath::vec3 cameraFront;
    bool firstMouse;
};
}