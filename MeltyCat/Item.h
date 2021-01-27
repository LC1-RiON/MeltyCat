#pragma once
#include "Object.h"
class Item : public Object{
private:

public:
	Item(int x, int y, int r, int put);
	~Item();

	void Update();
	void Draw();

	int GetX();
	int GetY();
	int GetPut();

	void SetX(int x);
	void SetY(int y);
	void SetPut(int put);
};

