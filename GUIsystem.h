#pragma once
#include <iostream>
#include "SFML\Graphics.hpp"

class GUIstyle
{
public:
	GUIstyle();
	GUIstyle(sf::Font* font, float borderSize, 	sf::Color bodyColor, sf::Color bodyHighlightColor, sf::Color borderColor, sf::Color borderHighlightColor, sf::Color textColor, sf::Color textHighlightColor);

	sf::Color bodyColor;
	sf::Color bodyHighlightColor;
	sf::Color borderColor;
	sf::Color borderHighlightColor;
	sf::Color textColor;
	sf::Color textHighlightColor;
	sf::Font* font;

	float borderSize;
};

class GUIentry
{
public:
	GUIentry();
	GUIentry(const std::string& message, sf::RectangleShape shape, sf::Text text);

	sf::RectangleShape shape;
	std::string message;
	sf::Text text;
};

class GUI : public sf::Transformable, public sf::Drawable
{
public:
	GUI(sf::Vector2f dimensions, int padding, bool horizontal, GUIstyle& style, std::vector<std::pair<std::string, std::string>> entries);
	sf::Vector2f getSize();
	int getEntry(const sf::Vector2f mousePos);
	void setEntryText(int entry, std::string text);
	void setDimensions(sf::Vector2f dimensions);
	void show();
	void hide();
	void highlight(const int entry);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<GUIentry> entries;
	bool visible;
	std::string activate(const int entry);
	std::string activate(const sf::Vector2f mousePos);

private:

	bool horizontal;
	GUIstyle style;
	sf::Vector2f dimensions;
	int padding;
};
