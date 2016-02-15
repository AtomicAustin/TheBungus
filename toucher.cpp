#include "toucher.h"

Toucher::Toucher()
{}
Toucher::Toucher(sf::Vector2f position, const std::string& name, Player& player)
{
	mToucherTexture.loadFromFile(name);
	mToucher.setTexture(mToucherTexture);
	mToucher.setPosition(position);
	player.addCollider(mToucher.getGlobalBounds());
}
void Toucher::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mToucher, states);
}
