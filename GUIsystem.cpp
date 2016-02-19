#include "GUIsystem.h"

GUI::GUI(){};
GUI::GUI(sf::Vector2f dimensions, sf::Vector2f position, sf::Color BackgroundColor, sf::Color borderColor)
{
	background.setSize(dimensions);
	background.setFillColor(backgroundColor);
	background.setOutlineThickness(5);
	background.setOutlineColor(borderColor);
	background.setPosition(position);
	visible = false;
	buttonReference = 0;
}
int GUI::addButton(sf::Vector2f dimensions, sf::Vector2f position, const std::string& text, sf::Color buttonColor, sf::Color borderColor, sf::Color textColor, sf::Font font)
{
	buttons.push_back(Button(dimensions, position, text, buttonColor, borderColor, textColor, font)); 
	buttonReference++;
	std::cout << "button #" << buttonReference << " made." << std::endl;
	return buttonReference;
}
int GUI::update()
{
	//or buttons.empty
	if(visible == false || buttons.empty()) 
		return -1;

	sf::Vector2i mousePosition = sf::Mouse::getPosition();
	for(int i = 0; i < buttonReference-1; i++)
	{
		if(buttons[i].buttonBackground.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			buttons[i].hovering();

			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				return i;
			}
		}
		else
			buttons[i].notHovering();
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
	
	/*for(Button iterate : buttons)
	{
		target.draw(iterate.buttonBackground);
		target.draw(iterate.buttonText);
	}*/

	for(int i = 0; i < buttonReference-1; i++)
	{
		std::cout << "drawing button" << i << std::endl;
		target.draw(buttons[i].buttonBackground);
		target.draw(buttons[i].buttonText);
	}

	std::cout << "drawing background" << std::endl;
	target.draw(background);

}
Button::Button(sf::Vector2f dimensions, sf::Vector2f position, const std::string& text, sf::Color buttonColor, sf::Color borderColor, sf::Color textColor, sf::Font font)
{
	buttonBackground.setSize(dimensions);
	buttonBackground.setPosition(position);
	buttonBackground.setFillColor(buttonColor);
	buttonBackground.setOutlineColor(borderColor);
	buttonBackground.setOutlineThickness(-2);

	buttonText.setString(text);
	buttonText.setPosition(position.x + 3, position.y + 3);
	buttonText.setColor(textColor);
	buttonText.setFont(font);
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
