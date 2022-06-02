#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

static GLuint texName;

typedef struct tagBITMAPHEADER {
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    RGBQUAD hRGB[256];
}BITMAPHEADER;

BYTE* LoadBitmapFile(BITMAPHEADER* bitmapHeader, int* imgSize, const char* filename)
{
    FILE* fp = fopen(filename, "rb");	
    if (fp == NULL)
    {
        printf("파일로딩에 실패했습니다.\n");	
        return NULL;
    }
    else
    {
        fread(&bitmapHeader->bf, sizeof(BITMAPFILEHEADER), 1, fp);
        fread(&bitmapHeader->bi, sizeof(BITMAPINFOHEADER), 1, fp);	
        fread(&bitmapHeader->hRGB, sizeof(RGBQUAD), 256, fp);	

        int imgSizeTemp = bitmapHeader->bi.biWidth * bitmapHeader->bi.biHeight;	
        *imgSize = imgSizeTemp;	// 이미지 사이즈를 상위 변수에 할당

        BYTE* image = (BYTE*)malloc(sizeof(BYTE) * imgSizeTemp);	
        fread(image, sizeof(BYTE), imgSizeTemp, fp);
        fclose(fp);


        return image;
    }
}

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
    //종료 이미지 세팅
    void gameOverBitMap(void)
    {
        glClearColor(0.0, 0.0, 0.0, 0.0);

        BITMAPHEADER originalHeader;	
        int imgSize;			
        BYTE* image = LoadBitmapFile(&originalHeader, &imgSize, "gameover.bmp"); 
        if (image == NULL) return;     

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glGenTextures(10, &texName);
        glBindTexture(GL_TEXTURE_2D, texName);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
            GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RED, GL_BYTE, image);
    }
    //스타트 이미지 세팅 
    void startBitMap(void)
    {
        glClearColor(0.0, 0.0, 0.0, 0.0);

        BITMAPHEADER originalHeader;
        int imgSize;
        BYTE* image = LoadBitmapFile(&originalHeader, &imgSize, "start.bmp");
        if (image == NULL) return;

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glGenTextures(10, &texName);
        glBindTexture(GL_TEXTURE_2D, texName);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
            GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_GREEN, GL_BYTE, image);
    }

};

