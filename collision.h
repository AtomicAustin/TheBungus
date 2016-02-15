#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Object;

class Collision
{
public:
	static bool axisCheck(float, float, float, float);
	static int checkCollision(sf::FloatRect, sf::FloatRect);
};
