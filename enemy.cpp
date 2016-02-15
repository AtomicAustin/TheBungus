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
}
void Enemy::path(Player* player, sf::Clock* clock)
{
	if(player->getBox().intersects(sight.getGlobalBounds()))
	{
		if((player->getPosition().x + 8) < position.x)
		{
			velocity.x = -1;
			xDirection(-1);
			setSight(2);
		}
		
		if((player->getPosition().x + 8) > position.x)
		{
			velocity.x = 1;
			xDirection(1);
			setSight(4);
		}
		
		if(player->getPosition().y > position.y)
		{
			velocity.y = 1;
			yDirection(1);
			setSight(3);
		}
		
		if(player->getPosition().y < position.y)
		{
			velocity.y = -1;
			yDirection(-1);
			setSight(1);
		}
		if(!player->getBox().intersects(mSprite.getGlobalBounds()))
		{
			if(clock->getElapsedTime().asSeconds() > 0.1f)
			{		
					walking();
					clock->restart();
			}
		}
	}
	else
		velocity = sf::Vector2f (0,0);
}
void Enemy::move(Player* player)
{
	if(player->getBox().intersects(mSprite.getGlobalBounds()))
		velocity = sf::Vector2f(0,0);

	position.x += velocity.x;
	position.y += velocity.y;
	//setSight(sightDirection);
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
/*void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
*{
*	states.transform *= getTransform();
*	target.draw(mSprite, states);
*}
*/
