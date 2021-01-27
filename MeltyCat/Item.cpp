#include "DxLib.h"
#include "Item.h"

Item::Item(int x, int y, int r, int put){
	this->x = x;
	this->y = y;
	this->r = r;
	this->put = put;
}
Item::~Item(){}

void Item::Update(){}

void Item::Draw(){
	if (put == 1) {
		DrawCircle(x, y, r, GetColor(112, 112, 255), true);
	}
}

int Item::GetX(){ return x; }
int Item::GetY(){ return y; }
int Item::GetPut(){ return put; }

void Item::SetX(int x){ this->x = x; }
void Item::SetY(int y){ this->y = y; }
void Item::SetPut(int put){ this->put = put; }
