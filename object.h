#pragma once

#include <SFML/Graphics.hpp>
#include "animate.h"

class Object: public sf::Sprite, public sf::Texture, public Animate
{
public:
	Object();
	Object(const std::string& name, sf::Vector2f position);
	virtual std::string kill();
	sf::FloatRect getBox();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//sf::Sprite mObject;
	//sf::Texture mObjectTexture;
};
