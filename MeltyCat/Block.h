#pragma once
#include "Object.h"
class Block : public Object{
private:
	int put, vector;
public:
	Block(int x, int y, int put, int vector);
	~Block();

	int GetX();
	int GetY();
	int GetPut();
	int GetVector();

	void SetX(int x);
	void SetY(int y);
	void SetPut(int put);
	void SetVector(int vector);
};

