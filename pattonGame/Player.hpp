class Player {
//플레이어 x,y좌표설정
public: 
	float playerX;
	float playerY;
	Player() {
		playerX = 0;
		playerY = 0;
	};
	~Player() {};
//키 이벤트 설정
	void upPressed() {
		playerY = 0.3f;
	}
	void downPressed() {
		playerY = -0.3f;
	}
	void zeroPressed() {
		playerY = 0.0f;
	}
};