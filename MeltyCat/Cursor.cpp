#include "Cursor.h"

Cursor::Cursor(int x, int y, int putX, int putY, int vector){
	this->x = x;
	this->y = y;
	this->putX = putX;
	this->putY = putY;
	this->vector = vector;
}
Cursor::~Cursor(){}

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
