#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "bits.cpp"

class SaveLoad 
{
public:
	static Bits load(bool);
	static bool save(sf::Vector2f position);
};
