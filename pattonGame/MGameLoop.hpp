#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include "Player.hpp"
#include "Enemy.hpp"

#pragma comment(lib,"OpenGL32")
using namespace std;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

namespace Engine
{
    class GameLoop
    {
    private:
        Player player;
        Enemy enemy;
        bool GameRunning = true;
        
    private:
        void reStart() {
            if (GetAsyncKeyState(VK_SHIFT) & 0x8000 || GetAsyncKeyState(VK_SHIFT) & 0x8001)
            {
                GameRunning = true;
                enemy.enemyX[0] = 1;
                enemy.enemyX[1] = 1;
                enemy.enemyX[2] = 1;
            }
        }
    public:
        void Input() {
            if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8001)
            {
                player.upPressed();
            }
            else if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8001)
            {
                player.downPressed();
            }
            else 
            {
                player.zeroPressed();
            }
        }
        void Run()
        {
            Update();
        }
    private:
        void Update() {
           
            GLFWwindow* window;
            glfwSetErrorCallback(error_callback);
            if (!glfwInit())
            {
                exit(EXIT_FAILURE);
            }
            window = glfwCreateWindow(1080, 640, "Simple example", NULL, NULL);
            if (!window)
            {
                glfwTerminate();
                exit(EXIT_FAILURE);
            }
            glfwMakeContextCurrent(window);
            glfwSetKeyCallback(window, key_callback);

            do
            {
                glClearColor(0, 0, 0, 0);
                glClear(GL_COLOR_BUFFER_BIT);
                //road width
                glBegin(GL_QUADS);

                glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
                glVertex3f(-1.0f, 0.22f, 0.0f);
                glVertex3f(-1.0f, 0.38f, 0.0f);
                glVertex3f(1.0f, 0.38f, 0.0f);
                glVertex3f(1.0f, 0.22f,0.0f);
                glEnd();

                glBegin(GL_QUADS);

                glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
                glVertex3f(-1.0f, -0.08f, 0.0f);
                glVertex3f(-1.0f, 0.08f, 0.0f);
                glVertex3f(1.0f, 0.08f, 0.0f);
                glVertex3f(1.0f, -0.08f, 0.0f);
                glEnd();

                glBegin(GL_QUADS);

                glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
                glVertex3f(-1.0f, -0.22f, 0.0f);
                glVertex3f(-1.0f, -0.38f, 0.0f);
                glVertex3f(1.0f, -0.38f, 0.0f);
                glVertex3f(1.0f, -0.22f, 0.0f);
                glEnd();

                glBegin(GL_QUADS);
                glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
                glVertex3f(-0.08f, 0.3f, 0.0f);
                glVertex3f(0.08f, 0.3f, 0.0f);
                glVertex3f(0.08f, -0.3f, 0.0f);
                glVertex3f(-0.08f, -0.3f, 0.0f);
                glEnd();

                ///player
                glPointSize(30);
                glBegin(GL_POINTS);
                glColor3f(0.359375f, 0.99609375f, 0.81640625f);
                glVertex2f(player.playerX, player.playerY);

                
                //enemy
                glPointSize(10);
                glBegin(GL_POINTS);
                glColor3f((float)(rand() % 100) / 100, (float)(rand() % 100) / 100, (float)(rand() % 100) / 100);
                for (int i = 0; i < 3; i++) {
                    glVertex2f(enemy.enemyX[i], enemy.enemyY[i]);
                }
                glEnd();

                //충돌
                if (player.playerX == 0 && player.playerY == -0.3f)
                {
                    if (enemy.enemyX[0] < 0.03f && enemy.enemyX[0] > -0.03f)
                    {
                        GameRunning = false;
                    }
                }
                if (player.playerX == 0 && player.playerY == 0)
                {
                    if (enemy.enemyX[1] < 0.03f && enemy.enemyX[1] > -0.03f)
                    {
                        GameRunning = false;
                    }
                }
                if (player.playerX == 0 && player.playerY == 0.3f)
                {
                    if (enemy.enemyX[2] < 0.03f && enemy.enemyX[2] > -0.03f)
                    {
                        GameRunning = false;
                    }
                }
            
                if (GameRunning == true)
                {
                    Input();
                    enemy.enemyCome();
                }
                if (GameRunning == false)
                {
                    cout << " 게임 종료";
                    glClearColor(1, 0, 0, 0);
                    glClear(GL_COLOR_BUFFER_BIT);

                    glEnd();
                    reStart();
                }

                glfwSwapBuffers(window);
                glfwPollEvents();

            } while (!glfwWindowShouldClose(window));

            glfwDestroyWindow(window);
            glfwTerminate();
            exit(EXIT_SUCCESS);
        }
    };
}