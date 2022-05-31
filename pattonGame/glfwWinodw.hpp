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
    //������ üũ
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
    //�����ִ��� Ȯ�ο���
    int windowwhile()
    {
        return glfwWindowShouldClose(window);
    }
    //�׷��� frame Ȯ�� �� �̺�Ʈ ó��
    void checkWindowEvent()
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //�̹�Ʈ ����
    void endWindow()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_SUCCESS);
    }
};

