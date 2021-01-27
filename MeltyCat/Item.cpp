#include "Item.h"

Item::Item(int x, int y, int put){
	this->x = x;
	this->y = y;
	this->put = put;
}
Item::~Item(){}

int Item::GetX(){ return x; }
int Item::GetY(){ return y; }
int Item::GetPut(){ return put; }

void Item::SetX(int x){ this->x = x; }
void Item::SetY(int y){ this->y = y; }
void Item::SetPut(int put){ this->put = put; }
