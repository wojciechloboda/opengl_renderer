#pragma once

#include "GLFW/glfw3.h"
#include "renderer.h"
#include "imgui_impl_glfw.h"


namespace GLFW
{
    
class Window
{
public:
    Window(int width, int height)
    {
        if(!glfwInit())
        {
            fprintf(stderr, "Failed to init GLFW\n");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, "Renderer", NULL, NULL);

        if (window == NULL)
        {
            fprintf(stderr, "Failed to create GLFW window\n");
        }

        //glfwSetInputMode(window, GLFW_CURSOR,  GLFW_CURSOR_DISABLED);
        //ImGui_ImplGlfw_InitForOpenGL(, true);
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

    void disableCursor()
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void activateCursor()
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    GLFWwindow* get()
    {
        return window;
    }

private:
    GLFWwindow* window;
    double lastX, lastY, yaw = 0.0, pitch = 0.0;
    vmath::vec3 cameraFront;
    bool firstMouse;
};
}