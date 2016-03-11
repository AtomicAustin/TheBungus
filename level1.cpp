#include "level1.h"

level1::level1()
{
	if(!map.loadFromFile("png/level1/level1.png"))
		std::cout << "Could not load file" << std::endl;
	actionCnt = 0;
	smap.setTexture(map);
	pause = new int[3];
}
int level1::level1Display(sf::RenderWindow* window, Bits bits)
{
	gameWindow = window;
	
	setBits(bits);
	setUp();

    while (gameWindow->isOpen())
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
			gameWindow->close();

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			pClock->restart();
			pauseMenu->show();
			while(pauseMenu->visible)
			{
				sf::Vector2f mousePosition = gameWindow->mapPixelToCoords(sf::Mouse::getPosition(*gameWindow), *view);
				switch(pauseMenu->update(view->getCenter(), mousePosition))
				{
					case 1: pauseMenu->hide(); break;
					//case 2: options menu
					case 3: gameWindow->close(); break;
				}

				if(pClock->getElapsedTime().asSeconds() > .1f && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					pauseMenu->hide();

				updateWindow();
			}
		}

		sf::Event event;

        while (gameWindow->pollEvent(event))
        {
			if(event.type == sf::Event::Closed)
				gameWindow->close();
			if(event.type == sf::Event::KeyReleased)
				player->keyReleased(event);
		}
		
		update();

    }
	return -1;
}
void level1::setUp()
{
	populate();

	pClock = new sf::Clock;
	eClock = new sf::Clock;
	
	view = new sf::View();
	view->reset(sf::FloatRect(0,0,300,200));

	makePauseMenu();
	
	gameWindow->setFramerateLimit(30);
}
void level1::updateWindow()
{
	gameWindow->setView(*view);
	gameWindow->clear();
	gameWindow->draw(smap);
	gameWindow->draw(*player);

	for(auto& i:objects)
		gameWindow->draw(*i);
	for(auto& i:enemies)
		gameWindow->draw(*i);
	for(auto& i:items)
		gameWindow->draw(*i);

	if(pauseMenu->visible)
		gameWindow->draw(*pauseMenu);

	gameWindow->display();
}
void level1::setBits(Bits &bits)
{
	player = new Player("png/player/herofull33x24.png", sf::Vector2i(33,24), gameWindow->getSize(), bits.position);

	//initialize everything else
}
void level1::populate()
{
	enemies.push_back(std::unique_ptr<Enemy>(new Enemy("png/enemy/portalmaster17x21.png", sf::Vector2i(17,21), sf::Vector2f(256,128))));
	objects.push_back(std::unique_ptr<Object>(new Object("png/level1/tree.png", sf::Vector2f(50,100))));
	for(auto& i: objects)
	{
		player->addCollider(i->getBox());
	}
}
void level1::makePauseMenu()
{
	sf::Vector2f guiPosition(view->getCenter().x - 50, view->getCenter().y-75);

	pauseMenu = new GUI(sf::Vector2f(100, 150), guiPosition, sf::Color (0x66, 0xb3, 0xff), sf::Color (0x00, 0x00, 0x33));
	std::string resume = "Resume";
	std::string options = "Options";
	std::string quit = "Quit";
	std::string fontName = "font/00TT.ttf";

	sf::Font* font = new sf::Font;
	if(!font->loadFromFile(fontName))
		std::cout << "couldn't load font" << std::endl;

	pause[0] = pauseMenu->addButton(sf::Vector2f(96, 35), sf::Vector2f(guiPosition.x+2, guiPosition.y+10), resume, sf::Color (0x00, 0x66, 0xff), sf::Color (0x00, 0x1f, 0x4d), sf::Color (0xcc, 0xe0, 0xff), font);
	pause[1] = pauseMenu->addButton(sf::Vector2f(96, 35), sf::Vector2f(guiPosition.x+2, guiPosition.y+55), options, sf::Color (0x00, 0x66, 0xff), sf::Color (0x00, 0x1f, 0x4d), sf::Color (0xcc, 0xe0, 0xff), font);
	pause[2] = pauseMenu->addButton(sf::Vector2f(96, 35), sf::Vector2f(guiPosition.x+2, guiPosition.y+100), quit, sf::Color (0x00, 0x66, 0xff), sf::Color (0x00, 0x1f, 0x4d), sf::Color (0xcc, 0xe0, 0xff), font);
}
void level1::updateView()
{
	if(player->getPosition().x > view->getCenter().x+75)
		view->move(1,0);
	if(player->getPosition().x < view->getCenter().x-75)
		view->move(-1,0);		
	if(player->getPosition().y > view->getCenter().y+50)
		view->move(0,1);
	if(player->getPosition().y < view->getCenter().y-50)
		view->move(0,-1);
}
void level1::update()
{
	sf::FloatRect* playerMovementBox = player->getBox();
	for(auto& i: enemies)
	{
		i->move(playerMovementBox);
		i->path(playerMovementBox, eClock);
	}

	delete playerMovementBox;
	playerMovementBox = NULL;

	if(actionCnt > 3)
	{
		player->deleteAction();
		actionCnt = 0;
	}

	if(actionCnt > 0)
	{
		sf::FloatRect* playerAction = player->action(actionCnt);
		enemies.erase(std::remove_if(enemies.begin(), enemies.end(), 
			[&](std::unique_ptr<Enemy> const&e) -> bool
		{
			if(playerAction->intersects(e.get()->getBox()))
			{
				e.get()->kill();
				return true;
			}
			return false;
		}));
		delete playerAction;
		playerAction = NULL;
	}

	player->move(pClock, actionCnt);

	updateView();
	updateWindow();
}
level1::~level1()
{
	gameWindow = NULL;
	delete view;
	delete pClock;
	delete eClock;
	delete player;
	enemies.clear();
	objects.clear();
	delete pauseMenu;
	delete[] pause;
}
