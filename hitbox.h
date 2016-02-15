#pragma once

#include "SFML/Graphics.hpp"

class Hitbox
{
public:
	Hitbox();
	Hitbox(sf::FloatRect);
	void updateBox(sf::FloatRect);
	sf::FloatRect getBox();
private:
	sf::FloatRect mBox;
};
