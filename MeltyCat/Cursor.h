#pragma once
#include "Object.h"
class Cursor : public Object{
private:
	int putX, putY, vector;
public:
	Cursor(int x, int y, int putX, int putY, int vector);
	~Cursor();

	int GetX();
	int GetY();
	int GetPutX();
	int GetPutY();
	int GetVector();

	void SetX(int x);
	void SetY(int y);
	void SetPutX(int putX);
	void SetPutY(int putY);
	void SetVector(int Vector);
};

