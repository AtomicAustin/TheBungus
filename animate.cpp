#include "animate.h"

Object_Animate::Object_Animate()
{}
void Object_Animate::setup(sf::Vector2i dimensions, int width, int height)
{
	for(int i = 0; i < width; i++)
		left.push_back(dimensions.x * i);
	for(int j = 0; j < height; j++)
		top.push_back(dimensions.y * j);
	iterate = 0;
	offset = 0;
}
void Object_Animate::animate()
{
	if(iterate == 3 + offset)
		iterate = offset;
	else
		iterate++;

	spriteRect.left = left[iterate];
	mSprite.setTextureRect(spriteRect);
}
void Object_Animate::reset()
{
	spriteRect.left = left[0];
	mSprite.setTextureRect(spriteRect);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
Moveable_Animate::Moveable_Animate()
{}
//used for the special case when one direction is released but another is still pressed
void Moveable_Animate::releaseDirection(sf::Vector2f velocity)
{
	if(velocity == sf::Vector2f (0,-1))
		spriteRect.top = top[1];
	else if(velocity == sf::Vector2f (1,0))
		spriteRect.top = top[3];
	else if(velocity == sf::Vector2f (0,1))
		spriteRect.top = top[0];
	else if(velocity == sf::Vector2f (-1,0))
		spriteRect.top = top[2];

	mSprite.setTextureRect(spriteRect);
}
void Moveable_Animate::xDirection(int direction)
{
	if(direction == 1)
		spriteRect.top = top[3];
	else
		spriteRect.top = top[2];
	mSprite.setTextureRect(spriteRect);
}
void Moveable_Animate::yDirection(int direction)
{
	if(direction == 1)
		spriteRect.top = top[0];
	else
		spriteRect.top = top[1];
	mSprite.setTextureRect(spriteRect);
}
void Moveable_Animate::setOffSet(int action)
{
	//walking
	if(action==0)
	{
		spriteRect.left = left[0];
		offset, iterate = 0;
	}
	//swinging
	else if(action==1)
	{
		spriteRect.left = left[4];
		offset, iterate = 4;
	}
	//swinging and walking
	else if(action == 2)
	{
		spriteRect.left = left[8];
		offset, iterate = 8;
	}
	mSprite.setTextureRect(spriteRect);
}
