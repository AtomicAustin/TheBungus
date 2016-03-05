#include "object.h"

Object::Object()
{}
Object::Object(const std::string& name, sf::Vector2f position)
{
	mTexture.loadFromFile(name);
	mSprite.setTexture(mTexture);
	mSprite.setPosition(position);
	this->position = position;
}
sf::FloatRect Object::getBox()
{
	return mSprite.getGlobalBounds();
}
void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}
