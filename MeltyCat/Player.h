#pragma once
class Player {
private:
	int x, y, r, moveX, moveY, state;
public:
	Player(int x, int y, int r, int moveX, int moveY, int state);
	~Player();
};
