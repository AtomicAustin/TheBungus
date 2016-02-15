#pragma once

#include "SFML\Graphics.hpp"
#include <iostream>

class Animate
{
public:
	Animate();
	void setup(sf::Vector2i, int width, int height);
	void walking();
	void releaseDirection(sf::Vector2f);
	void xDirection(int direction);
	void yDirection(int direction);
	void setDimensions(sf::Vector2i);
	void setOffSet(int action);
protected:
	sf::IntRect spriteRect;
	int offset;
	int iterate;
	int left[12];
	int top[4];

	//The whole sprite sheet
	sf::Texture mTexture;
	//The actual sprite, this is what the user sees
	sf::Sprite mSprite;
};
