#pragma once
#include "Object.h"
class Item : public Object{
private:

public:
	Item(int x, int y, int put);
	~Item();

	int GetX();
	int GetY();
	int GetPut();

	void SetX(int x);
	void SetY(int y);
	void SetPut(int put);
};

