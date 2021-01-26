#pragma once
class Collision
{
private:
	char flag;
	int move_x;
	int move_y;
	float hang;

public:
	Collision();
	~Collision() {};
	
	void update(char direction);
};
