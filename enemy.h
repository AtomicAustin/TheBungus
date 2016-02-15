#pragma once

#include <SFML\Graphics.hpp>
#include "animate.h"
#include "player.h"

class Enemy: public Object //public sf::Transformable, public Animate
{
public:

	Enemy();
	Enemy(const std::string &name, sf::Vector2i dimensions, sf::Vector2f mPosition);
	virtual void path(Player* player, sf::Clock* clock);
	virtual void move(Player* player);
	virtual std::string kill();
	void setSight(int sightDirection);
	void setEnPosition(sf::Vector2f position);
	sf::RectangleShape getSight();
	sf::FloatRect getBox();
	

private:
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int sightDirection;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::RectangleShape sight;
};
