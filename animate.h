#pragma once

#include "SFML\Graphics.hpp"
#include <iostream>

class Object_Animate
{
public:
	Object_Animate();
	void setup(sf::Vector2i, int width, int height);
	void animate();
	void reset();
protected:
	sf::IntRect spriteRect;
	int offset;
	int iterate;
	std::vector<int> left;
	std::vector<int> top;

	//The whole sprite sheet
	sf::Texture mTexture;
	//The actual sprite, this is what the user sees
	sf::Sprite mSprite;
};
class Moveable_Animate: public Object_Animate
{
public:
	Moveable_Animate();
	void releaseDirection(sf::Vector2f);
	void xDirection(int direction);
	void yDirection(int direction);
	void setOffSet(int action);
}
