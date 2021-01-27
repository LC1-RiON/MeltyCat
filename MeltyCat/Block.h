#pragma once
#include "Object.h"
class Block : public Object{
private:
	int vector;
public:
	Block(int x, int y, int r, int put, int vector);
	~Block();

	void Update();
	void Draw();

	int GetX();
	int GetY();
	int GetPut();
	int GetVector();

	void SetX(int x);
	void SetY(int y);
	void SetPut(int put);
	void SetVector(int vector);
};

