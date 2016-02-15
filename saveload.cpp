#include "saveload.h"

Bits SaveLoad::load(bool existingFile)
{
	Bits bits;
	if(existingFile == true)
	{
		float position[2];
		int filePosition = 0;
		std::ifstream file("save.txt");
		std::string line;
		if(file.is_open())
		{
			while(std::getline(file,line))
			{
				float tempdata = std::stof(line);
				position[filePosition] = tempdata;
				filePosition++;
			}
			bits.position = sf::Vector2f(position[0],position[1]);
			file.close();
			return bits;
		}
		std::cout << "Couldn't load data" << std::endl;
		bits.position = sf::Vector2f(150,150);
		return bits;
	}
	else
	{
		bits.position = sf::Vector2f(150,150);
		return bits;
	}
}
bool SaveLoad::save(sf::Vector2f position)
{
	std::ofstream file("save.txt");
	if(file.is_open())
	{
		file << position.x;
		file << position.y;
		file.close();
		return true;
	}
	else
		return false;
}	
