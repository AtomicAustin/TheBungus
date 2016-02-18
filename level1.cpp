#include "level1.h"

level1::level1()
{
	if(!map.loadFromFile("png/level1/level1.png"))
		std::cout << "Could not load file" << std::endl;
	actionCnt = 0;

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
					sf::Font pFont;
					pFont.loadFromFile("00TT.ttf");
					GUIstyle(&pFont, 5, sf::Color::Blue, sf::Color::Green, sf::Color::Black, sf::Color::Yellow, sf::Color::Black, sf::Color::White);

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
