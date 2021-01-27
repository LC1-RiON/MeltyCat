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

void Player::Move(int edgeL, int WIN_WIDTH, int WIN_HEIGHT){
	x += moveX;
	y += moveY;
	if (x < edgeL + r || x > WIN_WIDTH - r) {
		moveX = -moveX;
	}
	if (y < 0 + r || y > WIN_HEIGHT - r) {
		moveY = -moveY;
	}
}

void Player::Turn(Block* block){/*LU=0,LD=1,RD=2,RU=3*/
	if (x == block->GetX() && y == block->GetY() && moveX > 0) {
		if (block->GetVector() == 0) {
			moveX = 0;
			moveY = -2;
		}
		else if (block->GetVector() == 1) {
			moveX = 0;
			moveY = 2;
		}
	}
	else if (x == block->GetX() && y == block->GetY() && moveX < 0) {
		if (block->GetVector() == 3) {
			moveX = 0;
			moveY = -2;
		}
		else if (block->GetVector() == 2) {
			moveX = 0;
			moveY = 2;
		}
	}
	else if (x == block->GetX() && y == block->GetY() && moveY > 0) {
		if (block->GetVector() == 0) {
			moveX = -2;
			moveY = 0;
		}
		else if (block->GetVector() == 3) {
			moveX = 2;
			moveY = 0;
		}
	}
	else if (x == block->GetX() && y == block->GetY() && moveY < 0) {
		if (block->GetVector() == 1) {
			moveX = -2;
			moveY = 0;
		}
		else if (block->GetVector() == 2) {
			moveX = 2;
			moveY = 0;
		}
	}
}

void Player::Switch(Item* item, int edgeL){
	if (item->GetPut() == 1 && (x - edgeL) / 64 == (item->GetX() - edgeL) / 64 && y / 64 == item->GetY() / 64) {
		item->SetPut(0);
		state++;
		if (state > 1/*LIQUID*/) {
			state = 0/*SOLID*/;
		}
	}
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
