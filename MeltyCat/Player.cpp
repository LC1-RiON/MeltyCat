#include "Player.h"

Player::Player(int x, int y, int r, int moveX, int moveY, int state) {
	this->x = x;
	this->y = y;
	this->r = r;
	this->moveX = moveX;
	this->moveY = moveY;
	this->state = state;
}
Player::~Player() {}
