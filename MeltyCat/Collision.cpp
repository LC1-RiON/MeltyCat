#include "Collision.h"

Collision::Collision() {
	char flag = false;
	int move_x = 0;
	int move_y = 0;
	float hang = 0.6;
}

void Collision::update(char direction) {
	if (flag == false)
	{
		if (direction == 1)
		{
			move_y -= 20;
			flag = true;
		}
		else if (direction == 2)
		{
			move_y += 20;
			flag = true;
		}
		else if (direction == 3)
		{
			move_x -= 20;
			flag = true;
		}
		else if (direction == 4)
		{
			move_x += 20;
			flag = true;
		}
	}

	else if (flag == true)
	{
		if (direction == 1)
		{
			move_y = move_y * hang;
			flag = true;
		}
		else if (direction == 2)
		{
			move_y = move_y * hang;
			flag = true;
		}
		else if (direction == 3)
		{
			move_x = move_x * hang;
			flag = true;
		}
		else if (direction == 4)
		{
			move_x = move_x * hang;
			flag = true;
		}
	}
}

