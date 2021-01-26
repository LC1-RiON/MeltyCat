#pragma once
#include "Object.h"
class Player : public Object {
private:
	int moveX, moveY, state;
public:
	Player(int x, int y, int r, int moveX, int moveY, int state);
	~Player();

	int GetX();
	int GetY();
	int GetR();
	int GetMoveX();
	int GetMoveY();
	int GetState();

	void SetX(int x);
	void SetY(int y);
	void SetR(int r);
	void SetMoveX(int moveX);
	void SetMoveY(int moveY);
	void SetState(int state);
};
