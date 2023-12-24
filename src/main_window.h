
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cstdio>

class MainWindow {
public:
    static Scene *scene;
    static double lastX, lastY, yaw, pitch;
    static glm::vec3 cameraFront;
    static bool firstMouse;
    static bool activeInput;

    MainWindow(MainWindow &other) = delete;
    void operator=(const MainWindow &) = delete;

    static MainWindow& Instance(int width, int height) { 
        static MainWindow instance(width, height); 
        return instance; 
    }

    void setInputActive() {
        MainWindow::activeInput = true;
    }

    void disableCursor()
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void activateCursor()
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    bool shouldClose()
    {
        return glfwWindowShouldClose(window);
    }

    void processInput(double deltaTime)
    {
        if(MainWindow::scene == nullptr) {
            return;
        }

        float cameraSpeed = 2.5f * deltaTime;
        if (activeInput) {
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                MainWindow::scene->mainCamera.position += cameraSpeed * MainWindow::scene->mainCamera.cameraFront;
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            {
                MainWindow::scene->mainCamera.position -= cameraSpeed * MainWindow::scene->mainCamera.cameraFront;
            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                MainWindow::scene->mainCamera.position -= glm::normalize(
                    glm::cross(MainWindow::scene->mainCamera.upDirection, MainWindow::scene->mainCamera.cameraFront)) * cameraSpeed;
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                MainWindow::scene->mainCamera.position += glm::normalize(
                    glm::cross(MainWindow::scene->mainCamera.upDirection, MainWindow::scene->mainCamera.cameraFront)) * cameraSpeed;
            }
        }
            
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            ImGui::SetWindowFocus(NULL);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            MainWindow::activeInput = false;
        }      
    }

    void setScene(Scene *scene) {
        MainWindow::scene = scene; 
    }

    void swapBuffers()
    {
        glfwSwapBuffers(window);
    }

private: 
    MainWindow(int width, int height) {
        if(!glfwInit())
        {
            fprintf(stderr, "Failed to init GLFW\n");
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, "Renderer", NULL, NULL);

        if (window == NULL)
        {
            fprintf(stderr, "Failed to create GLFW window\n");
            return;
        }       

        //context and function loading
        glfwMakeContextCurrent(window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            fprintf(stderr, "Failed to initialize GLAD\n");
            return;
        }  
        glViewport(0, 0, width, height);

        //dear imgui context
        const char* glsl_version = "#version 430";
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        MainWindow::scene = nullptr;
        MainWindow::lastX = 0; 
        MainWindow::lastY = 0;
        MainWindow::yaw = 0;
        MainWindow::pitch = 0;

        glfwSetCursorPosCallback(window, MainWindow::mouse_callback); 
        glfwSetWindowSizeCallback(window, MainWindow::window_size_callback); 
        glfwSetFramebufferSizeCallback(window, MainWindow::framebuffer_size_callback);
    }

    static void window_size_callback(GLFWwindow* window, int width, int height)
    {
    }

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }  

    static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        ImGuiIO& io = ImGui::GetIO();

        if (MainWindow::activeInput)
        {
            if (MainWindow::firstMouse)
            {
                MainWindow::lastX = xpos;
                MainWindow::lastY = ypos;
                MainWindow::firstMouse = false;
            }
        
            float xoffset =  MainWindow::lastX - xpos;
            float yoffset = ypos - MainWindow::lastY; 
            MainWindow::lastX = xpos;
            MainWindow::lastY = ypos;

            float sensitivity = 0.1f;
            xoffset *= sensitivity;
            yoffset *= sensitivity;

            MainWindow::yaw   += xoffset;
            MainWindow::pitch += yoffset;

            if(MainWindow::pitch > 89.0f)
                MainWindow::pitch = 89.0f;
            if(MainWindow::pitch < -89.0f)
                MainWindow::pitch = -89.0f;

            glm::vec3 direction;
            direction[0] = cos(glm::radians(MainWindow::yaw)) * cos(glm::radians(MainWindow::pitch));
            direction[1] = sin(glm::radians(MainWindow::pitch));
            direction[2] = sin(glm::radians(MainWindow::yaw)) * cos(glm::radians(MainWindow::pitch));
            MainWindow::cameraFront = glm::normalize(direction);
            if (MainWindow::scene != nullptr) {
                MainWindow::scene->mainCamera.cameraFront = MainWindow::cameraFront;
            }
        }
    }  

    ~MainWindow()
    {
        glfwTerminate();
    }

    GLFWwindow* window;
};

Scene *MainWindow::scene;
double MainWindow::lastX, MainWindow::lastY, MainWindow::yaw, MainWindow::pitch;
glm::vec3 MainWindow::cameraFront;
bool MainWindow::firstMouse;
bool MainWindow::activeInput;