#include "DxLib.h"
#include "Cursor.h"

Cursor::Cursor(int x, int y, int r, int putX, int putY, int vector){
	this->x = x;
	this->y = y;
	this->r = r;
	this->putX = putX;
	this->putY = putY;
	this->vector = vector;
}
Cursor::~Cursor(){}

void Cursor::Update(int edgeL,
char* keys, char* oldkeys,
int click, int oldclick, Block* block,
int WIN_WIDTH, int WIN_HEIGHT){
	Drag(edgeL);
	Spin(keys, oldkeys);
	Put(click, oldclick, block);
}

void Cursor::Drag(int edgeL){
	GetMousePoint(&x, &y);
	putX = (x - edgeL) / 64 * 64 + edgeL + 32;
	putY = y / 64 * 64 + 32;
}

void Cursor::Spin(char* keys, char* oldkeys){
	if (keys[KEY_INPUT_LSHIFT] == 1 && oldkeys[KEY_INPUT_LSHIFT] == 0) {
		vector++;
		if (vector > 3) {/*LU=0,LD=1,RD=2,RU=3*/
			vector = 0;
		}
	}
}

void Cursor::Put(int click, int oldclick, Block* block){
	if ((oldclick & MOUSE_INPUT_LEFT) == 0 && (click & MOUSE_INPUT_LEFT) == 1) {
		block->SetX(putX);
		block->SetY(putY);
		block->SetVector(vector);
		block->SetPut(1);
	}
}

void Cursor::Draw(int edgeL, int WIN_WIDTH, int WIN_HEIGHT){
	if (x >= edgeL && x <= WIN_WIDTH && y >= 0 && y <= WIN_HEIGHT) {
		DrawBox(putX - 32, putY - 32, putX + 32, putY + 32, GetColor(255, 255, 0), false);
	}
	switch (vector) {/*LU=0,LD=1,RD=2,RU=3*/
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

int Cursor::GetX(){ return x; }
int Cursor::GetY(){ return y; }
int Cursor::GetPutX(){ return putX; }
int Cursor::GetPutY(){ return putY; }
int Cursor::GetVector(){ return vector; }

void Cursor::SetX(int x){ this->x = x; }
void Cursor::SetY(int y){ this->y = y; }
void Cursor::SetPutX(int putX){ this->putX = putX; }
void Cursor::SetPutY(int putY){ this->putY = putY; }
void Cursor::SetVector(int Vector){ this->vector = vector; }
