#include "DxLib.h"
#include "Block.h"

Block::Block(int x, int y, int r, int put, int vector){
	this->x = x;
	this->y = y;
	this->r = r;
	this->put = put;
	this->vector = vector;
}
Block::~Block(){}

void Block::Update(){}

void Block::Draw(){
	if (put == 1) {/*LU=0,LD=1,RD=2,RU=3*/
		switch (vector) {
		case 0:
			DrawTriangle(x - r, y + r, x + r, y - r, x + r, y + r, GetColor(192, 255, 192), true);
			break;

		case 1:
			DrawTriangle(x - r, y - r, x + r, y + r, x + r, y - r, GetColor(192, 255, 192), true);
			break;

		case 2:
			DrawTriangle(x + r, y - r, x - r, y + r, x - r, y - r, GetColor(192, 255, 192), true);
			break;

		case 3:
			DrawTriangle(x + r, y + r, x - r, y - r, x - r, y + r, GetColor(192, 255, 192), true);
			break;
		}
	}
}

int Block::GetX(){ return x; }
int Block::GetY(){ return y; }
int Block::GetPut(){ return put; }
int Block::GetVector(){ return vector;}

void Block::SetX(int x){ this->x = x; }
void Block::SetY(int y) { this->y = y; }
void Block::SetPut(int put){ this->put = put; }
void Block::SetVector(int vector){ this->vector = vector; }
