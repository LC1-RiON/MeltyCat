#pragma once
#include "Block.h"
#include "Object.h"
class Cursor : public Object{
private:
	int putX, putY, vector;
public:
	Cursor(int x, int y, int putX, int putY, int vector);
	~Cursor();

	void Update();
	void Drag(int edgeL);
	void Spin(char* keys, char* oldkeys);
	void Put(int click, int oldclick, Block* block);
	void Draw(int edgeL, int WIN_WIDTH, int WIN_HEIGHT);

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

