#include "enemy.h"

Enemy::Enemy()
{}
Enemy::Enemy(const std::string& name, sf::Vector2i dimensions, sf::Vector2f mPosition)
{
	velocity = sf::Vector2f(0,0);

	spriteRect.left = 0;
	spriteRect.top = 0;
	spriteRect.width = dimensions.x;
	spriteRect.height = dimensions.y;

	setup(dimensions, 4, 4);

	if(!mTexture.loadFromFile(name))
		std::cout << "Can't load enemy sprite" << std::endl;

	mSprite.setTexture(mTexture);
	mSprite.setTextureRect(spriteRect);

	position = mPosition;
	setSight(3);

	moving = NONE;
	spotted = false;
}
void Enemy::path(sf::FloatRect* pMoveBox, sf::Clock* clock)
{
	if(pMoveBox->intersects(sight.getGlobalBounds()))
	{
		spotted = true;
	}

	if(!spotted)
		return;
	else
	{
		switch(findPlayer(pMoveBox))
		{
		case 0: 
			{
				if((pMoveBox->left) < position.x)
				{
					velocity.x = -.7;
					moving = LEFT;
				}
		
				if((pMoveBox->left) > position.x)
				{
					velocity.x = .7;
					moving = RIGHT;
				}
				break;
			}
		case 1:
			{
				if(pMoveBox->top > position.y)
				{
					velocity.y = .7;
					moving = DOWN;
				}
		
				if(pMoveBox->top < position.y)
				{
					velocity.y = -.7;
					moving = UP;
				}
			}
		}

		if(!pMoveBox->intersects(mSprite.getGlobalBounds()))
		{
			if(clock->getElapsedTime().asSeconds() > 0.1f)
			{		
				animate();
				clock->restart();
			}
		}
		else moving = NONE;
	}
}
int Enemy::findPlayer(sf::FloatRect* pMoveBox)
{
	if(abs(pMoveBox->left - position.x) > abs(pMoveBox->top - position.y))
		return 0;
	return 1;
}
void Enemy::move(sf::FloatRect* pMoveBox)
{
	if(pMoveBox->intersects(mSprite.getGlobalBounds()))
		velocity = sf::Vector2f(0,0);

	switch(moving)
	{
	case NONE: {reset(); break;}
	case UP: { yDirection(-1);setSight(1); break;}
	case DOWN: { yDirection(1);setSight(3); break;}
	case LEFT: { xDirection(-1);setSight(2); break;}
	case RIGHT: { xDirection(1);setSight(4); break;}
	}

	position.x += velocity.x;
	position.y += velocity.y;
	mSprite.setPosition(position);
}
void Enemy::kill()
{
	//run death animation
}
void Enemy::setSight(int direction)
{
	switch(direction)
		{
			//facing up
		case 1:{ sight.setPosition(position.x-15, position.y-68); sight.setSize(sf::Vector2f(62,100)); break;}
			//facing left
		case 2:{ sight.setPosition(position.x-68, position.y-15); sight.setSize(sf::Vector2f(100,62)); break;}
			   //facing down
		case 3:{ sight.setPosition(position.x-15, position.y); sight.setSize(sf::Vector2f(62,100)); break;}
			   //facing right
		case 4:{ sight.setPosition(position.x, position.y-15); sight.setSize(sf::Vector2f(100,62)); break;}
		}
}
sf::RectangleShape Enemy::getSight()
{
	return sight;
}
