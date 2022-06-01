#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <Windows.h>

#include "Player.hpp"
#include "Enemy.hpp"
#include "glfwWinodw.hpp"

#pragma comment(lib,"OpenGL32")
using namespace std;

static GLuint texName;

//비트맵 헤더를 한 묶음으로 다시 구조체로 묶었어요. 함수처리를 편하게 하려구요.
typedef struct tagBITMAPHEADER {
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    RGBQUAD hRGB[256];
}BITMAPHEADER;

BYTE* LoadBitmapFile(BITMAPHEADER* bitmapHeader, int* imgSize, const char* filename)
{
    FILE* fp = fopen(filename, "rb");	//파일을 이진읽기모드로 열기
    if (fp == NULL)
    {
        printf("파일로딩에 실패했습니다.\n");	//fopen에 실패하면 NULL값을 리턴
        return NULL;
    }
    else
    {
        fread(&bitmapHeader->bf, sizeof(BITMAPFILEHEADER), 1, fp);	//비트맵파일헤더 읽기
        fread(&bitmapHeader->bi, sizeof(BITMAPINFOHEADER), 1, fp);	//비트맵인포헤더 읽기
        fread(&bitmapHeader->hRGB, sizeof(RGBQUAD), 256, fp);	//색상팔렛트 읽기

        int imgSizeTemp = bitmapHeader->bi.biWidth * bitmapHeader->bi.biHeight;	//이미지 사이즈 계산
        *imgSize = imgSizeTemp;	// 이미지 사이즈를 상위 변수에 할당

        BYTE* image = (BYTE*)malloc(sizeof(BYTE) * imgSizeTemp);	//이미지크기만큼 메모리할당
        fread(image, sizeof(BYTE), imgSizeTemp, fp);//이미지 크기만큼 파일에서 읽어오기
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
            init();
            glwindow.checkWindow();  //윈도우 조건 체크
            do
            {
                Update();
            } while (!glwindow.windowwhile()); //윈도우 켜져있는지 확인여부
            glwindow.endWindow(); //윈도우 종료

        }
    private:
        void init(void)
        {
            glClearColor(0.0, 0.0, 0.0, 0.0);

            BITMAPHEADER originalHeader;	//비트맵의 헤더부분을 파일에서 읽어 저장할 구조체
            int imgSize;			//이미지의 크기를 저장할 변수
            BYTE* image = LoadBitmapFile(&originalHeader, &imgSize, "lena_gray.bmp"); //비트맵파일을 읽어 화소정보를 저장
            if (image == NULL) return;        //파일 읽기에 실패하면 프로그램 종료

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

                cout << " 게임 종료";
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
            

            
            glwindow.checkWindowEvent(); //이벤트 확인      
        }
    };
}