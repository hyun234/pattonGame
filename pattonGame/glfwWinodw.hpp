#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
class glfwWindow 
{
    GLFWwindow* window;
private:
    static void error_callback(int error, const char* description)
    {
        fputs(description, stderr);
    }
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }
   
public:
    //윈도우 체크
	void checkWindow() 
    {
        glfwSetErrorCallback(error_callback);
        if (!glfwInit())
        {
            exit(EXIT_FAILURE);
        }
        window = glfwCreateWindow(1080, 640, "Game", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        glfwMakeContextCurrent(window);
        glfwSetKeyCallback(window, key_callback);
	}
    //켜져있는지 확인여부
    int windowwhile()
    {
        return glfwWindowShouldClose(window);
    }
    //그려질 frame 확인 후 이벤트 처리
    void checkWindowEvent()
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //이밴트 종료
    void endWindow()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }
};

