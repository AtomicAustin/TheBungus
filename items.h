#pragma once

#include <SFML/Graphics.hpp>
#include "player.h"

class Item: public Object
{
public:
	Item();
	Item(const std::string& name, sf::Vector2f position);
	void drop();
	int getTag();
private:
	int tag;
};
/*class ItemManager
{
public:

};*/
