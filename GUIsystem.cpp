#include "GUIsystem.h"

GUI::GUI(){};
GUI::GUI(sf::Vector2f dimensions, sf::Vector2f position, sf::Color BackgroundColor, sf::Color borderColor)
{
	background.setSize(dimensions);
	background.setFillColor(BackgroundColor);
	background.setOutlineThickness(2);
	background.setOutlineColor(borderColor);
	background.setPosition(position);
	visible = false;
	buttonReference = 0;
}
int GUI::addButton(sf::Vector2f dimensions, sf::Vector2f position, const std::string& text, sf::Color buttonColor, sf::Color borderColor, sf::Color textColor, sf::Font* font)
{
	buttons.push_back(Button(dimensions, position, text, buttonColor, borderColor, textColor, font)); 
	buttonReference++;
	return buttonReference;
}
int GUI::update(const sf::Vector2f viewPosition, sf::Vector2f &mousePosition)
{
	if(visible == false || buttons.empty()) 
		return -1;

	background.setPosition(viewPosition.x - 50, viewPosition.y-75);
	for(int i=0; i < buttonReference; i++)
	{
		buttons[i].setPosition(sf::Vector2f(background.getPosition().x + 2, background.getPosition().y + ( 10 + 45 * i)));
	}

	for(int i = 0; i < buttonReference; i++)
	{
		if(buttons[i].checkHovering(mousePosition))
		{
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
				return i+1;
		}
	}
	return -1;
}
void GUI::show()
{
	visible = true;
}
void GUI::hide()
{
	visible = false;
}
void GUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(visible == false) 
		return;

	states.transform *= getTransform();
	target.draw(background);
	for(int i = 0; i < buttonReference; i++)
	{
		target.draw(buttons[i].buttonBackground);
		target.draw(buttons[i].buttonText);
	}
}
Button::Button(sf::Vector2f dimensions, sf::Vector2f position, const std::string& text, sf::Color buttonColor, sf::Color borderColor, sf::Color textColor, sf::Font* font)
{
	buttonBackground.setSize(dimensions);
	buttonBackground.setPosition(position);
	buttonBackground.setFillColor(buttonColor);
	buttonBackground.setOutlineColor(borderColor);
	buttonBackground.setOutlineThickness(-1);

	buttonText.setString(text);
	buttonText.setPosition(position.x + 3, position.y + 3);
	buttonText.setColor(textColor);
	buttonText.setFont(*font);
	buttonText.setCharacterSize(18);
}
bool Button::checkHovering(sf::Vector2f mousePosition)
{
	if(buttonBackground.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
	{
		hovering();
		return true;
	}
	notHovering();
	return false;
}
void Button::hovering()
{
	//background (0x00, 0x66, 0xff), background outline (0x00, 0x1f, 0x4d), text color (0xcc, 0xe0, 0xff)
	buttonBackground.setFillColor(sf::Color (0x00, 0x52, 0xcc));
	buttonBackground.setOutlineColor(sf::Color(0x00, 0x0a, 0x1a));
	buttonText.setColor(sf::Color (0x99, 0xc2, 0xff));
}
void Button::notHovering()
{
	buttonBackground.setFillColor(sf::Color (0x00, 0x66, 0xff));
	buttonBackground.setOutlineColor(sf::Color (0x00, 0x1f, 0x4d));
	buttonText.setColor(sf::Color (0xcc, 0xe0, 0xff));
}
void Button::setPosition(sf::Vector2f position)
{
	buttonBackground.setPosition(position);
	buttonText.setPosition(position.x + 3, position.y + 3);
}
