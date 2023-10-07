#pragma once

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

class InputHandler
{
public:
    InputHandler(GLFW::Window &window, Scene &scene)
        : window(window), scene(scene)
    {
        window.setUserPointer(this);
        setCallbacks();
    }

    void setCallbacks()
    {
        window.setFramebufferSizeCallback(InputHandler::framebuffer_size_callback);
        window.setCursorPosCallback(InputHandler::mouse_callback);
        window.setWindowSizeCallback(InputHandler::window_size_callback);  
    }

    void removeCallbacks()
    {
        window.setFramebufferSizeCallback(NULL);
        window.setCursorPosCallback(NULL);
        window.setWindowSizeCallback(NULL); 
    }


    void processInput(double deltaTime)
    {
        float cameraSpeed = 2.5f * deltaTime;
        if (activeInput)
        {
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
                scene.mainCamera.position -= glm::normalize(
                    glm::cross(scene.mainCamera.upDirection, scene.mainCamera.cameraFront)) * cameraSpeed;
            }
            if (window.getKey(GLFW_KEY_D) == GLFW_PRESS)
            {
                scene.mainCamera.position += glm::normalize(
                    glm::cross(scene.mainCamera.upDirection, scene.mainCamera.cameraFront)) * cameraSpeed;
            }
        }
            
        if(window.getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            ImGui::SetWindowFocus(NULL);
            window.activateCursor();
            activeInput = false;
        }      
    }

    bool activeInput = false;

    private:

    static void window_size_callback(GLFWwindow* window, int width, int height)
    {
        InputHandler *handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
        //handler->renderer.onResize(width, height);
    }

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }  

    static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        ImGuiIO& io = ImGui::GetIO();
        InputHandler *handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));

        if (handler->activeInput)
        {
            if (handler->firstMouse)
            {
                handler->lastX = xpos;
                handler->lastY = ypos;
                handler->firstMouse = false;
            }
        
            float xoffset =  handler->lastX - xpos;
            float yoffset = ypos - handler->lastY; 
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

            glm::vec3 direction;
            direction[0] = cos(glm::radians(handler->yaw)) * cos(glm::radians(handler->pitch));
            direction[1] = sin(glm::radians(handler->pitch));
            direction[2] = sin(glm::radians(handler->yaw)) * cos(glm::radians(handler->pitch));
            handler->cameraFront = glm::normalize(direction);
            handler->scene.mainCamera.cameraFront = handler->cameraFront;

        }
    }  
    Scene &scene;
    GLFW::Window &window;

    double lastX, lastY, yaw = 0.0, pitch = 0.0;
    glm::vec3 cameraFront;
    bool firstMouse;
};