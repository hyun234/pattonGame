class Player {
//�÷��̾� x,y��ǥ����
public: 
	float playerX;
	float playerY;
	Player() {
		playerX = 0;
		playerY = 0;
	};
	~Player() {};
//Ű �̺�Ʈ ����
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