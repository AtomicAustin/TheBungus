#include "GUIsystem.h"

GUI::GUI(){};
GUI::GUI(sf::Vector2f dimensions, sf::Vector2f position, sf::Color BackgroundColor, sf::Color borderColor)
{
	background.setSize(dimensions);
	background.setFillColor(backgroundColor);
	background.setOutlineThickness(5);
	background.setOutlineColor(borderColor);
	background.setPosition(position);

	buttonReference = 0;
}
int GUI::addButton(sf::Vector2f dimensions, sf::Vector2f position, std::string& text, sf::Color buttonColor, sf::Color borderColor, sf::Color textColor, std::string& fontName)
{
	buttons.push_back(new Button(dimensions, position, text, buttonColor, borderColor, textColor, fontName));
	if(buttonReference !=0) buttonReference++;

	return buttonReference;
}
int GUI::update()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition();
	for(int i = 0; i <= buttonReference; i++)
	{
		if(buttons[i]->buttonBackground.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			buttons[i]->hovering();

			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				return i;
			}
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
	if(!visible) return;

	for(int i = 0; i <= buttonReference; i++)
	{
		target.draw(buttons[i]->buttonBackground);
		target.draw(buttons[i]->buttonText);
	}
	target.draw(background);

}
Button::Button(sf::Vector2f dimensions, sf::Vector2f position, std::string& text, sf::Color buttonColor, sf::Color borderColor, sf::Color textColor, std::string& font)
{
	buttonBackground.setSize(dimensions);
	buttonBackground.setPosition(position);
	buttonBackground.setFillColor(buttonColor);
	buttonBackground.setOutlineColor(borderColor);
	buttonBackground.setOutlineThickness(-2);

	buttonText.setString(text);
	buttonText.setPosition(position.x + 3, position.y + 3);
	buttonText.setColor(textColor);
	textFont->loadFromFile(font);
	buttonText.setFont(*textFont);
}
void Button::hovering()
{
	buttonBackground.setFillColor(sf::Color::Black);
	buttonBackground.setOutlineColor(sf::Color::Black);
	buttonText.setColor(sf::Color::Black);
}
