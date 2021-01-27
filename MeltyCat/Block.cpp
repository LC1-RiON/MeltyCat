#include "Block.h"

Block::Block(int x, int y, int put, int vector){
	this->x = x;
	this->y = y;
	this->put = put;
	this->vector = vector;
}
Block::~Block(){}

int Block::GetX(){ return x; }
int Block::GetY(){ return y; }
int Block::GetPut(){ return put; }
int Block::GetVector(){ return vector;}

void Block::SetX(int x){ this->x = x; }
void Block::SetY(int y) { this->y = y; }
void Block::SetPut(int put){ this->put = put; }
void Block::SetVector(int vector){ this->vector = vector; }
