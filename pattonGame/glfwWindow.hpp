#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <Windows.h>

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

}
namespace LJH
{
    class glfwWindow 
    {
        GLFWwindow* window;
    public:
        void settingWindow() {
            glfwSetErrorCallback(error_callback);
            if (!glfwInit())
            exit(EXIT_FAILURE);
            window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
            if (!window)
            {
                glfwTerminate();
                exit(EXIT_FAILURE);
            }
            glfwMakeContextCurrent(window);
            glfwSetKeyCallback(window, key_callback);
        }
    public: 
        void eventCheck() {
                glfwSwapBuffers(window);
                glfwPollEvents();
        }
    public:

    };
    
}



