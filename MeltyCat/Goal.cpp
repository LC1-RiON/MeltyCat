#include "DxLib.h"
#include "Goal.h"

Goal::Goal(int x, int y, int r){
	this->x = x;
	this->y = y;
	this->r = r;
}
Goal::~Goal(){}

void Goal::Update(){}

void Goal::Draw(){
	DrawCircle(x, y, r, GetColor(255, 192, 255), true);
}
