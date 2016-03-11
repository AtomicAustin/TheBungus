#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "animate.h"
#include "collision.h"
#include "object.h"

// What the user controls, this does all sort of things
class Player : public sf::Drawable, public sf::Transformable, public Moveable_Animate
{
public:
	Player();
	Player(const std::string& name, sf::Vector2i(dimensions), sf::Vector2u size, sf::Vector2f mPosition);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void keyReleased(sf::Event);
	sf::FloatRect* action(int& actionCount);
	void updateAction(int direction);
	void deleteAction();
	void addCollider(sf::FloatRect);
	void addObject(Object);
	void move(sf::Clock*,int& actionCount);
	sf::FloatRect* getBox();
	sf::Vector2f getPosition();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	int mActionCnt;
	sf::Vector2u wSize;
	sf::Vector2f velocity;
	sf::Vector2f position;
	std::vector<sf::FloatRect> colliders;
	bool moving, swinging;
	sf::FloatRect movementRect;
	sf::RectangleShape actionRect;
	bool hit;
	Object* wasHit;
	int movingDirection;
};
