#include <SFML\Graphics.hpp>
#include <iostream>
#include "animate.h"
#include "player.h"
#include "enemy.h"
#include "object.h"
#include "bits.cpp"
#include "GUIsystem.h"

class level1
{
public:
	level1();
	~level1();
	void level1Display(sf::RenderWindow &gameWindow, Bits);
protected:
	int actionCnt;
	sf::View view;
	sf::IntRect screenDimension;
	sf::Texture map;
	sf::Sprite smap;
};
