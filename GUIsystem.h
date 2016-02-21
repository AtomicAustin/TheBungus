#pragma once
#include <iostream>
#include "SFML\Graphics.hpp"

class Button; 
class GUI : public sf::Transformable, public sf::Drawable
{
public:
	GUI();
	//dimensions, position, background color, border color
	GUI(sf::Vector2f dimensions, sf::Vector2f position, sf::Color BackgroundColor, sf::Color borderColor);
	//dimensions, position, text, button color, border color textcolor, font name ".txt"
	int addButton(sf::Vector2f dimensions, sf::Vector2f position, const std::string& text, sf::Color buttonColor, sf::Color borderColor, sf::Color textColor, sf::Font* font);
	int update(const sf::Vector2f viewPosition, sf::Vector2f &mousePosition);
	void show();
	void hide();
	sf::Vector2f getPosition();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool visible;
	std::vector<Button> buttons;
private:
	sf::RectangleShape background;
	int buttonReference;
};

class Button
{
public:
	Button();
	Button(sf::Vector2f dimensions, sf::Vector2f position, const std::string& text, sf::Color buttonColor, sf::Color borderColor, sf::Color textColor, sf::Font* font);
	bool checkHovering(sf::Vector2f);
	void hovering();
	void notHovering();
	void setPosition(sf::Vector2f);
	sf::RectangleShape buttonBackground;
	sf::Text buttonText;
};

/*class textGUI: public GUI
{
public:
	textGUI(bool active);
	void keyScroll();
	void setText(std::string* activeMessage);
	void storeText(std::string* storedMessage);
private:
	std::vector<std::string*> messages;
};
class InventoryGUI: public GUI
{
public:
	InventoryGUI(bool inventory, bool active);
	void updateInventory(bool inventory);
	int hovered(sf::Vector2f mousePosition);
	void showTooltip(int item);
	sf::Vector2f getMousePosition();
private:
	std::vector<sf::Vector2f> itemPositions;
	std::vector<int> items;
	
};
class CraftGUI: public GUI
{
}
class TradeGUI: public GUI
{
}
class TooltipGUI: public GUI
{
}
*/
