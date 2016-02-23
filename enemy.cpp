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
void Enemy::path(Player* player, sf::Clock* clock)
{
	if(player->getBox().intersects(sight.getGlobalBounds()))
	{
		spotted = true;
	}

	if(!spotted)
		return;
	else
	{
		switch(findPlayer(player))
		{
		case 0: 
			{
				if((player->getPosition().x + 8) < position.x)
				{
					velocity.x = -.7;
					moving = LEFT;
				}
		
				if((player->getPosition().x + 8) > position.x)
				{
					velocity.x = .7;
					moving = RIGHT;
				}
				break;
			}
		case 1:
			{
				if(player->getPosition().y > position.y)
				{
					velocity.y = .7;
					moving = DOWN;
				}
		
				if(player->getPosition().y < position.y)
				{
					velocity.y = -.7;
					moving = UP;
				}
			}
		}

		if(!player->getBox().intersects(mSprite.getGlobalBounds()))
		{
			if(clock->getElapsedTime().asSeconds() > 0.1f)
			{		
					walking();
					clock->restart();
			}
		}
		else moving = NONE;
	}
}
int Enemy::findPlayer(Player* player)
{
	if(abs(player->getBox().left - position.x) > abs(player->getBox().top - position.y))
		return 0;
	return 1;
}
void Enemy::move(Player* player)
{
	if(player->getBox().intersects(mSprite.getGlobalBounds()))
		velocity = sf::Vector2f(0,0);

	switch(moving)
	{
	case NONE: {stopped(); break;}
	case UP: { yDirection(-1);setSight(1); break;}
	case DOWN: { yDirection(1);setSight(3); break;}
	case LEFT: { xDirection(-1);setSight(2); break;}
	case RIGHT: { xDirection(1);setSight(4); break;}
	}

	position.x += velocity.x;
	position.y += velocity.y;
	mSprite.setPosition(position);
}
std::string Enemy::kill()
{
	return "Enemy";
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
sf::FloatRect Enemy::getBox()
{
	return mSprite.getGlobalBounds();
}
