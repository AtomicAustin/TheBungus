#pragma once

#include <SFML\Graphics.hpp>
#include "animate.h"
#include "player.h"
#include <cmath>

class Enemy: public Animate, public sf::Transformable, public sf::Drawable
{
public:
	Enemy();
	Enemy(const std::string &name, sf::Vector2i dimensions, sf::Vector2f mPosition);
	void path(sf::FloatRect* pMoveBox, sf::Clock* clock);
	int findPlayer(sf::FloatRect* pMoveBox);
	void move(sf::FloatRect* pMoveBox);
	void kill();
	void setSight(int sightDirection);
	void setEnPosition(sf::Vector2f position);
	sf::FloatRect getBox();
	sf::RectangleShape getSight();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Vector2f position;
	enum movement{UP, DOWN, LEFT, RIGHT, NONE};
	movement moving;
	sf::Vector2f velocity;
	sf::RectangleShape sight;
	bool spotted;
};
