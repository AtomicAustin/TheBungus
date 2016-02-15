#include "player.h"

Player::Player()
{}
Player::Player(const std::string &name, sf::Vector2i dimensions, sf::Vector2u size, sf::Vector2f mPosition)
{
	position = sf::Vector2f(0,0);
	velocity = sf::Vector2f(0,0);

	wSize = size;

	spriteRect.left = 0;
	spriteRect.top = 0;
	
	setup(dimensions, 12, 4);
	setOffSet(0);
	spriteRect.width = dimensions.x;
	spriteRect.height = dimensions.y;
	
	mTexture.loadFromFile(name);
	mSprite.setTexture(mTexture);
	mSprite.setTextureRect(spriteRect);
	
	movementRect.left = position.x + 8;
	movementRect.top = position.y + 1;
	movementRect.width = 17;
	movementRect.height = 17;

	//15,17
	actionRect.setSize(sf::Vector2f(15,17));
	actionRect.setPosition(sf::Vector2f(0,0));

	position=mPosition;
	moving = false;
	swinging = false;
	hit = false;
	wasHit = NULL;
}
void Player::moveUp()
{
	velocity.y=-1;
	yDirection(-1);
	moving = true;
	movingDirection = 1;
}
void Player::moveDown()
{
	velocity.y=1;
	yDirection(1);
	moving = true;
	movingDirection = 2;
}
void Player::moveLeft()
{	
	velocity.x=-1;
	xDirection(-1);
	moving = true;
	movingDirection = 3;
}
void Player::moveRight()
{
	velocity.x=1;
	xDirection(1);
	moving = true;
	movingDirection = 4;
}
void Player::keyReleased(sf::Event event)
{
	switch(event.key.code)
	{
		case sf::Keyboard::W: velocity.y = 0; releaseDirection(velocity); break;
		case sf::Keyboard::S: velocity.y = 0; releaseDirection(velocity); break;
		case sf::Keyboard::A: velocity.x = 0; releaseDirection(velocity); break;
		case sf::Keyboard::D: velocity.x = 0; releaseDirection(velocity); break;
	}
	moving = false;
}
void Player::action(int& actionCount)
{
	if(actionCount == 1)
	{
		swinging = true;
		if(moving)
			setOffSet(2);
		else
			setOffSet(1);
	}	
	
	updateAction(movingDirection);
	
	if(hit && actionCount == 3)
	{
		hit = false;
		std::cout<< "Player hit: " << wasHit->kill() << std::endl;
		wasHit = NULL;
	}

	if(actionCount == 1)
	{
		for(size_t i = 0; i < objects.size(); i++)
		{
			if(actionRect.getGlobalBounds().intersects(objects[i]->getBox()))
			{	
				wasHit = objects[i];
				hit = true;
			}
		}
	}
}
void Player::updateAction(int direction)
{
	switch(direction)
	{
	case 1:{actionRect.setSize(sf::Vector2f(15,17)); actionRect.setPosition(sf::Vector2f(position.x + 8,position.y)); break;}
	case 2:{actionRect.setSize(sf::Vector2f(15,17)); actionRect.setPosition(sf::Vector2f(position.x + 8,position.y + 12)); break;}
	case 3:{actionRect.setSize(sf::Vector2f(25,12)); actionRect.setPosition(sf::Vector2f(position.x-5, position.y + 9)); break;}
	case 4:{actionRect.setSize(sf::Vector2f(25,12)); actionRect.setPosition(sf::Vector2f(position.x + 13,position.y + 9)); break;}
	}
}
void Player::deleteAction()
{
	setOffSet(0);
	swinging = false;
	//delete actionHitBox
}
void Player::move(sf::Clock* clock, int& actionCount)
{

	position.x += velocity.x;
	position.y += velocity.y;

	movementRect.left = position.x+8;
	movementRect.top = position.y+1;

	if(moving == true || swinging == true)
	{
		if(clock->getElapsedTime().asSeconds() > 0.1f)
		{
			walking();
			clock->restart();
			if(swinging)
					actionCount++;
		}
	}

	if(moving == false && swinging == false)
		setOffSet(0);

	for(size_t i = 0; i < colliders.size(); i++)
	{
		//if colliding with top
		if(Collision::checkCollision(movementRect, colliders[i]) == 1)
			position.y = colliders[i].top - 18;
		//if colliding with bottom
		else if(Collision::checkCollision(movementRect, colliders[i]) == 2)
			position.y = colliders[i].top + colliders[i].height - 1;
		//if colliding with left
		else if(Collision::checkCollision(movementRect, colliders[i]) == 3)
			position.x = colliders[i].left - 25;
		//if colliding with right
		else if(Collision::checkCollision(movementRect, colliders[i]) == 4)
			position.x = colliders[i].left + colliders[i].width - 8;
	}

	if(position.x < 0 || position.x > (wSize.x-19))
		position.x -= velocity.x;
	if(position.y < 0 || position.y > (wSize.y-25))
		position.y -= velocity.y;
	
	mSprite.setPosition(position);
}
void Player::addCollider(sf::FloatRect box)
{
	colliders.push_back(box);
}
void Player::addObject(Object* obj)
{
	objects.push_back(obj);
}
sf::FloatRect Player::getBox()
{
	return movementRect;
}
sf::Vector2f Player::getPosition()
{
	return position;
}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}
