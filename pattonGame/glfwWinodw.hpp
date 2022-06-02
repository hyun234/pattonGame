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
        printf("���Ϸε��� �����߽��ϴ�.\n");	
        return NULL;
    }
    else
    {
        fread(&bitmapHeader->bf, sizeof(BITMAPFILEHEADER), 1, fp);
        fread(&bitmapHeader->bi, sizeof(BITMAPINFOHEADER), 1, fp);	
        fread(&bitmapHeader->hRGB, sizeof(RGBQUAD), 256, fp);	

        int imgSizeTemp = bitmapHeader->bi.biWidth * bitmapHeader->bi.biHeight;	
        *imgSize = imgSizeTemp;	// �̹��� ����� ���� ������ �Ҵ�

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
    //���� �̹��� ����
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
    //��ŸƮ �̹��� ���� 
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

