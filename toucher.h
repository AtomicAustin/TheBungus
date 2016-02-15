#pragma once

#include <SFML/Graphics.hpp>
#include "player.h"


//This is unused and unfinished, ignore for now
//The idea here is to define objects that can be interacted with
class Toucher: public sf::Sprite, public sf::Texture
{
public:
	Toucher();
	Toucher(sf::Vector2f position, const std::string& name, Player& player);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite mToucher;
	sf::Texture mToucherTexture;
};
