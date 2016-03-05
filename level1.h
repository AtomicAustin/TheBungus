#include <SFML\Graphics.hpp>
#include <memory>
#include <iostream>
#include "animate.h"
#include "player.h"
#include "enemy.h"
#include "object.h"
#include "bits.cpp"
#include "GUIsystem.h"
#include "items.h"

class level1
{
public:
	level1();
	int level1Display(sf::RenderWindow* gameWindow, Bits);
	void setUp();
	void updateWindow();
	void setBits(Bits &bits);
	void populate();
	void makePauseMenu();
	void updateView();
	void update();
	~level1();

protected:
	sf::RenderWindow* gameWindow;
	int actionCnt;
	sf::View* view;

	sf::Clock* pClock;
	sf::Clock* eClock;

	//Pointers instantiated in setBits
	Player* player;
	/*inventory 
	level progress 
	ability tree 
	armor 
	weapons and enchantments
	safe items
	*/

	//Pointers instantiated in populate
	std::vector<std::unique_ptr<Object>> objects;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Item>> items;

	//stuff for the pause menu
	GUI *pauseMenu;
	int *pause;

	sf::Texture map;
	sf::Sprite smap;
};
