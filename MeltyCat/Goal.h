#pragma once
#include "Object.h"
class Goal : public Object{
private:

public:
	Goal(int x, int y, int r);
	~Goal();

	void Update();
	void Draw();
};

