#include "DxLib.h"
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

void Player::Update(){
}

void Player::Draw(){
	if (state == 0/*SOLID*/) {
		DrawCircle(x, y, r, GetColor(255, 255, 128), true);
	}
	else if (state == 1/*LIQUID*/) {
		DrawCircle(x, y, r, GetColor(128, 128, 255), true);
	}
}

int Player::GetX() { return x; }
int Player::GetY() { return y; }
int Player::GetR() { return r; }
int Player::GetMoveX() { return moveX; }
int Player::GetMoveY() { return moveY; }
int Player::GetState() { return state; }

void Player::SetX(int x) { this->x = x; }
void Player::SetY(int y) { this->y = y; }
void Player::SetR(int r) { this->r = r; }
void Player::SetMoveX(int moveX) { this->moveX = moveX; }
void Player::SetMoveY(int moveY) { this->moveY = moveY; }
void Player::SetState(int state) { this->state = state; }
