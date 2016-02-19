#include "level1.h"

level1::level1()
{
	if(!map.loadFromFile("png/level1/level1.png"))
		std::cout << "Could not load file" << std::endl;
	actionCnt = 0;
	menuIsOpen = false;
	smap.setTexture(map);
}
level1::~level1()
{}
void level1::level1Display(sf::RenderWindow &gameWindow, Bits bits)
{
	//gameWindow.setSize(map.getSize());

	Player* player = new Player("png/player/herofull33x24.png", sf::Vector2i(33,24), gameWindow.getSize(), bits.position);

	Enemy* enemy = new Enemy("png/enemy/portalmaster17x21.png", sf::Vector2i(17,21), sf::Vector2f(256,128));
	
	Object* tree = new Object("png/level1/tree.png", sf::Vector2f(50,100));
	player->addCollider(tree->getBox());

	player->addObject(enemy);
	player->addObject(tree);

	sf::Clock* pClock = new sf::Clock;
	sf::Clock* eClock = new sf::Clock;
	
	view.reset(sf::FloatRect(0,0,300,200));

	GUI pauseMenu(sf::Vector2f(200, 500), sf::Vector2f(450, 100), sf::Color (0x66, 0xb3, 0xff), sf::Color (0x00, 0x00, 0x33));
	std::string resume = "Resume";
	std::string options = "Options";
	std::string quit = "Quit";
	std::string fontName = "00TT.ttf";

	sf::Font font;
	if(!font.loadFromFile(fontName))
		std::cout << "couldn't load font" << std::endl;

	//add button takes a font not a string
	int pause[] = 
	{
		pauseMenu.addButton(sf::Vector2f(160, 40), sf::Vector2f(470, 130), resume, sf::Color (0x00, 0x66, 0xff), sf::Color (0x00, 0x1f, 0x4d), sf::Color (0xcc, 0xe0, 0xff), font),
		pauseMenu.addButton(sf::Vector2f(160, 40), sf::Vector2f(470, 200), options, sf::Color (0x00, 0x66, 0xff), sf::Color (0x00, 0x1f, 0x4d), sf::Color (0xcc, 0xe0, 0xff), font),
		pauseMenu.addButton(sf::Vector2f(160, 40), sf::Vector2f(470, 270), quit, sf::Color (0x00, 0x66, 0xff), sf::Color (0x00, 0x1f, 0x4d), sf::Color (0xcc, 0xe0, 0xff), font),
	};
	
	gameWindow.setFramerateLimit(30);

    while (gameWindow.isOpen())
    {  
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			player->moveUp();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			player->moveDown();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			player->moveLeft();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			player->moveRight();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			actionCnt = 1;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			gameWindow.close();

		enemy->path(player, eClock);

		sf::Event event;

        while (gameWindow.pollEvent(event))
        {
			if(event.type == sf::Event::Closed)
				gameWindow.close();
			if(event.type == sf::Event::KeyReleased)
				player->keyReleased(event);
			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Escape)
				{
					if(!pauseMenu.visible) 
					{
						std::cout << "Showing pause menu" << std::endl;
						pauseMenu.show();
					}
					else 
					{
						std::cout << "hiding pause menu" << std::endl;
						pauseMenu.hide();
					}
				}
			}
		}

		enemy->move(player);
		
		if(actionCnt > 3)
		{
			player->deleteAction();
			actionCnt = 0;
		}
		if(actionCnt > 0)
		{
			player->action(actionCnt);
		}

		player->move(pClock, actionCnt);

		if(player->getPosition().x > view.getCenter().x+75)
			view.move(1,0);
		if(player->getPosition().x < view.getCenter().x-75)
			view.move(-1,0);
		if(player->getPosition().y > view.getCenter().y+50)
			view.move(0,1);
		if(player->getPosition().y < view.getCenter().y-50)
			view.move(0,-1);

		if(pauseMenu.visible) 
			pauseMenu.update();

		gameWindow.draw(pauseMenu);
		gameWindow.setView(view);
        gameWindow.clear();
		gameWindow.draw(smap);
		gameWindow.draw(*player);
		gameWindow.draw(*enemy);
		gameWindow.draw(*tree);
		
		

		gameWindow.display();
	
    }

	delete enemy;
	delete player;
	delete tree;
	return;
}
