#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <Windows.h>

#include "Player.hpp"
#include "Enemy.hpp"
#include "glfwWinodw.hpp"

#pragma comment(lib,"OpenGL32")
using namespace std;

namespace LJH_Engine
{
    class GameLoop
    {
    private:
        Player player;
        Enemy enemy;
        bool GameRunning;
        glfwWindow glwindow;

    private:
        //다시 시작
        void reStart() {
            if (GetAsyncKeyState(VK_SHIFT) & 0x8000 || GetAsyncKeyState(VK_SHIFT) & 0x8001)
            {
                GameRunning = true;
                for (int i = 0; i < 3; i++) {
                    enemy.enemyX[i] = 1;
                }
            }
        }
        //키 입력
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
    public:
        void Run()
        {
            GameRunning = true;
            glwindow.checkWindow();  //윈도우 조건 체크
            while (!glwindow.windowwhile()) {
                Update();
            }
            //do
            //{
            //    Update();
            //} while (!glwindow.windowwhile()); //윈도우 켜져있는지 확인여부
            glwindow.endWindow(); //윈도우 종료

        }
    private:
        void Update() {
            if (GameRunning == true)
            {
                Input();
                enemy.enemyCome();
                glClearColor(0, 0, 0, 0);
                glClear(GL_COLOR_BUFFER_BIT);
                //road width
                glBegin(GL_QUADS);

                glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
                glVertex3f(-1.0f, 0.22f, 0.0f);
                glVertex3f(-1.0f, 0.38f, 0.0f);
                glVertex3f(1.0f, 0.38f, 0.0f);
                glVertex3f(1.0f, 0.22f, 0.0f);
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
                    if (enemy.enemyX[0] < 0.035f && enemy.enemyX[0] > -0.035f)
                    {
                        GameRunning = false;
                    }
                }
                if (player.playerX == 0 && player.playerY == 0)
                {
                    if (enemy.enemyX[1] < 0.035f && enemy.enemyX[1] > -0.035f)
                    {
                        GameRunning = false;
                    }
                }
                if (player.playerX == 0 && player.playerY == 0.3f)
                {
                    if (enemy.enemyX[2] < 0.035f && enemy.enemyX[2] > -0.035f)
                    {
                        GameRunning = false;
                    }
                }
            }
            if (GameRunning == false)
            {

                cout << "게임 종료 \n\n Shift 누르면 다시 시작\n\n";
                glwindow.bitMap();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
                glEnable(GL_TEXTURE_2D);
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
                glBindTexture(GL_TEXTURE_2D, texName);

                glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.0);  glVertex3f(-0.8f, -1.0f, 0.0f);
                glTexCoord2f(0.0, 1.0);  glVertex3f(-0.8f, 1.0f, 0.0f);
                glTexCoord2f(1.0, 1.0);  glVertex3f(0.8f, 1.0f, 0.0f);
                glTexCoord2f(1.0, 0.0);  glVertex3f(0.8f, -1.0f, 0.0f);
                glEnd();
                /*glBegin(GL_TRIANGLES);
                glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0.0);
                glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
                glTexCoord2f(0.5, 1.0); glVertex3f(0.0, 1.0, 0.0);

                glEnd();*/
                glFlush();
                glDisable(GL_TEXTURE_2D);
                reStart();
            }
            
            glwindow.checkWindowEvent(); //이벤트 확인      
        }
    };
}