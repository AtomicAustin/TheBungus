#include "hitbox.h"

Hitbox::Hitbox()
{}
Hitbox::Hitbox(sf::FloatRect box)
{
	mBox = box;
}
void Hitbox::updateBox(sf::FloatRect box)
{
	mBox = box;
}
sf::FloatRect Hitbox::getBox()
{
	return mBox;
}
