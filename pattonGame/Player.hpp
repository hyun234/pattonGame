#include <iostream>
using namespace std;
class Player {

public: 
	
	float playerX;
	float playerY;
	Player() {
		playerX = 0;
		playerY = 0;
	};
	~Player() {};
	
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