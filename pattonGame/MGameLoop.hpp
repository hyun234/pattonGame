#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <Windows.h>

#include "Player.hpp"
#include "Enemy.hpp"
#include "glfwWinodw.hpp"

#pragma comment(lib,"OpenGL32")
using namespace std;

static GLuint texName;

//��Ʈ�� ����� �� �������� �ٽ� ����ü�� �������. �Լ�ó���� ���ϰ� �Ϸ�����.
typedef struct tagBITMAPHEADER {
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    RGBQUAD hRGB[256];
}BITMAPHEADER;

BYTE* LoadBitmapFile(BITMAPHEADER* bitmapHeader, int* imgSize, const char* filename)
{
    FILE* fp = fopen(filename, "rb");	//������ �����б���� ����
    if (fp == NULL)
    {
        printf("���Ϸε��� �����߽��ϴ�.\n");	//fopen�� �����ϸ� NULL���� ����
        return NULL;
    }
    else
    {
        fread(&bitmapHeader->bf, sizeof(BITMAPFILEHEADER), 1, fp);	//��Ʈ��������� �б�
        fread(&bitmapHeader->bi, sizeof(BITMAPINFOHEADER), 1, fp);	//��Ʈ��������� �б�
        fread(&bitmapHeader->hRGB, sizeof(RGBQUAD), 256, fp);	//�����ȷ�Ʈ �б�

        int imgSizeTemp = bitmapHeader->bi.biWidth * bitmapHeader->bi.biHeight;	//�̹��� ������ ���
        *imgSize = imgSizeTemp;	// �̹��� ����� ���� ������ �Ҵ�

        BYTE* image = (BYTE*)malloc(sizeof(BYTE) * imgSizeTemp);	//�̹���ũ�⸸ŭ �޸��Ҵ�
        fread(image, sizeof(BYTE), imgSizeTemp, fp);//�̹��� ũ�⸸ŭ ���Ͽ��� �о����
        fclose(fp);


        return image;
    }
}

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
        //�ٽ� ����
        void reStart() {
            if (GetAsyncKeyState(VK_SHIFT) & 0x8000 || GetAsyncKeyState(VK_SHIFT) & 0x8001)
            {
                GameRunning = true;
                for (int i = 0; i < 3; i++) {
                    enemy.enemyX[i] = 1;
                }
            }
        }
        //Ű �Է�
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
            init();
            glwindow.checkWindow();  //������ ���� üũ
            do
            {
                Update();
            } while (!glwindow.windowwhile()); //������ �����ִ��� Ȯ�ο���
            glwindow.endWindow(); //������ ����

        }
    private:
        void init(void)
        {
            glClearColor(0.0, 0.0, 0.0, 0.0);

            BITMAPHEADER originalHeader;	//��Ʈ���� ����κ��� ���Ͽ��� �о� ������ ����ü
            int imgSize;			//�̹����� ũ�⸦ ������ ����
            BYTE* image = LoadBitmapFile(&originalHeader, &imgSize, "lena_gray.bmp"); //��Ʈ�������� �о� ȭ�������� ����
            if (image == NULL) return;        //���� �б⿡ �����ϸ� ���α׷� ����

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            glGenTextures(1, &texName);
            glBindTexture(GL_TEXTURE_2D, texName);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                GL_NEAREST);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RED, GL_BYTE, image);
        }

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
                for (int i = 0; i < 3; i++) {
                    glColor3f(1.0, 1.0, 0.0);
                    glVertex2f(enemy.enemyX[i], enemy.enemyY[i]);
                }
                glEnd();

                //�浹
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

                cout << " ���� ����";
                glClear(GL_COLOR_BUFFER_BIT);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
                glEnable(GL_TEXTURE_2D);
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
                glBindTexture(GL_TEXTURE_2D, texName);

                glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.0);  glVertex3f(-1.0f, -1.0f, 0.0f);
                glTexCoord2f(0.0, 1.0);  glVertex3f(-1.0f, 1.0f, 0.0f);
                glTexCoord2f(1.0, 1.0);  glVertex3f(1.0f, 1.0f, 0.0f);
                glTexCoord2f(1.0, 0.0);  glVertex3f(1.0f, -1.0f, 0.0f);
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
            

            
            glwindow.checkWindowEvent(); //�̺�Ʈ Ȯ��      
        }
    };
}