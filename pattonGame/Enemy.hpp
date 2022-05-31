
class Enemy {
//적 x,y 좌표 설정
private:
    float fixedY = -0.3f;
public:
    float enemyX[3];
    float enemyY[3];
	Enemy() {
        for (int i = 0; i < 3; i++) {
            enemyX[i] = 1;
            enemyY[i] = fixedY;
            fixedY += 0.3f;
        }
	};
    ~Enemy() {};
	void enemyCome() {
        //enemyX[0] 제일 아래 
        if (enemyX[0] <= -1)
        {
            enemyX[0] = 1;
        }
        else
        {
            enemyX[0] -= 0.0006f;
        }
        if (enemyX[1] <= -1)
        {
            enemyX[1] = 1;
        }
        else
        {
            enemyX[1] -= 0.0001f;
        }
        if (enemyX[2] <= -1)
        {
            enemyX[2] = 1;
        }
        else
        {
            enemyX[2] -= 0.0003f;
        }
	}
};