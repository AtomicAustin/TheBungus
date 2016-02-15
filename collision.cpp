#include "collision.h"

bool Collision::axisCheck(float x1, float y1, float x2, float y2)
{
	if((x1 - x2) >= (y1 - y2))
		return true;
	else
		return false;
}
int Collision::checkCollision(sf::FloatRect p, sf::FloatRect c)
{
	float x1 = p.left;
	float y1 = p.top;
	float w1 = p.width;
	float h1 = p.height;

	float x2 = c.left;
	float y2 = c.top;
	float w2 = c.width;
	float h2 = c.height;

	if(x1 > x2 &&  x1 < x2+w2)
	{
		if(y1 > y2 && y1 < y2+h2)
		{	
			if(axisCheck(x2+w2,y2+h2,x1,y1))
				return 2; //bottom
			else
				return 4; //right
		}
		if(y1+h1 > y2 && y1+h1 < y2+h2)
		{
			if(axisCheck(x2+w2,y1+h1,x1,y2))
				return 1; //top
			else
				return 4; //right
		}
	}

	if(x1+w1 > x2 && x1+w1 < x2+w2)
	{
		if(y1 > y2 && y1 < y2+h2)
		{
			if(axisCheck(x1+w1,y2+h2,x2,y1))
				return 2; //bottom
			else
				return 3; //left
		}

		if(y1+h1 > y2 && y1+h1 < y2+h2)
		{ 
			if(axisCheck(x1+w1,y1+h1,x2,y2))
				return 1; //top
			else
				return 3; //left
		}
	}
	return 0;
}
