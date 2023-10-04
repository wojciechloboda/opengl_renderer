#pragma once

class InputHandler
{
public:
    InputHandler(GLFW::Window &window, Renderer &renderer, Scene &scene)
        : window(window), renderer(renderer), scene(scene)
    {
        window.setFramebufferSizeCallback(InputHandler::framebuffer_size_callback);
        window.setCursorPosCallback(InputHandler::mouse_callback);
        window.setWindowSizeCallback(InputHandler::window_size_callback);

        window.setUserPointer(this);
    }


    void processInput(double deltaTime)
    {
        float cameraSpeed = 2.5f * deltaTime;
        if (window.getKey(GLFW_KEY_W) == GLFW_PRESS)
        {
            scene.mainCamera.position += cameraSpeed * scene.mainCamera.cameraFront;
        }
        if (window.getKey(GLFW_KEY_S) == GLFW_PRESS)
        {
            scene.mainCamera.position -= cameraSpeed * scene.mainCamera.cameraFront;
        }
        if (window.getKey(GLFW_KEY_A) == GLFW_PRESS)
        {
            scene.mainCamera.position -= vmath::normalize(
                vmath::cross(scene.mainCamera.cameraFront, scene.mainCamera.upDirection)) * cameraSpeed;
        }
        if (window.getKey(GLFW_KEY_D) == GLFW_PRESS)
        {
            scene.mainCamera.position += vmath::normalize(
                vmath::cross(scene.mainCamera.cameraFront, scene.mainCamera.upDirection)) * cameraSpeed;
        }
        if(window.getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            window.setShouldClose();
        }      
    }

    private:

    static void window_size_callback(GLFWwindow* window, int width, int height)
    {
        InputHandler *handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
        handler->renderer.onResize(width, height);
    }

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }  

    static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        InputHandler *handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));

        if (handler->firstMouse)
        {
            handler->lastX = xpos;
            handler->lastY = ypos;
            handler->firstMouse = false;
        }
    
        float xoffset = xpos - handler->lastX;
        float yoffset = handler->lastY - ypos; 
        handler->lastX = xpos;
        handler->lastY = ypos;

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        handler->yaw   += xoffset;
        handler->pitch += yoffset;

        if(handler->pitch > 89.0f)
            handler->pitch = 89.0f;
        if(handler->pitch < -89.0f)
            handler->pitch = -89.0f;

        vmath::vec3 direction;
        direction[0] = cos(vmath::radians(handler->yaw)) * cos(vmath::radians(handler->pitch));
        direction[1] = sin(vmath::radians(handler->pitch));
        direction[2] = sin(vmath::radians(handler->yaw)) * cos(vmath::radians(handler->pitch));
        handler->cameraFront = vmath::normalize(direction);
        handler->scene.mainCamera.cameraFront = handler->cameraFront;
    }  

    Renderer &renderer;
    Scene &scene;
    GLFW::Window &window;

    double lastX, lastY, yaw = 0.0, pitch = 0.0;
    vmath::vec3 cameraFront;
    bool firstMouse;
};