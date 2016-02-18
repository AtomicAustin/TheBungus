#include "GUIsystem.h"

GUIstyle::GUIstyle()
{}
GUIstyle::GUIstyle(sf::Font* font, float borderSize, sf::Color bodyColor, sf::Color bodyHighlightColor, sf::Color borderColor, sf::Color borderHighlightColor, sf::Color textColor, sf::Color textHighlightColor)
{
	this->bodyColor = bodyColor;
	this->bodyHighlightColor = bodyHighlightColor;
	this->borderColor = borderColor;
	this->borderHighlightColor = borderHighlightColor;
	this->textColor = textColor;
	this->textHighlightColor = textHighlightColor;
	this->font = font;
	this->borderSize = borderSize;
}
GUIentry::GUIentry()
{}
GUIentry::GUIentry(const std::string& message, sf::RectangleShape shape, sf::Text text)
{
	this->message = message;
	this->shape = shape;
	this->text = text;
}
GUI::GUI(sf::Vector2f dimensions, int padding, bool horizontal, GUIstyle& style, std::vector<std::pair<std::string, std::string>> entries)
{
	visible = false;
	this->horizontal = horizontal;
	this->style = style;
	this->dimensions = dimensions;
	this->padding = padding;
	
	sf::RectangleShape shape;
	shape.setSize(dimensions);
	shape.setFillColor(style.bodyColor);
	shape.setOutlineThickness(-style.borderSize);
	shape.setOutlineColor(style.borderColor);

	for(auto entry : entries)
	{
		sf::Text text;
		text.setString(entry.first);
		text.setFont(*style.font);
		text.setColor(style.textColor);
		text.setCharacterSize(dimensions.y - style.borderSize - padding);

		this->entries.push_back(GUIentry(entry.second, shape, text));
	}
}
sf::Vector2f GUI::getSize()
{
	return sf::Vector2f(this->dimensions.x, this->dimensions.y * this->entries.size());
}
int GUI::getEntry(const sf::Vector2f mousePos)
{
	if(entries.size() == 0) return -1;
	if(!this->visible) return -1;

	for(int i = 0; i < this->entries.size(); ++i)
	{

		sf::Vector2f point = mousePos;
		point += this->entries[i].shape.getOrigin();
		point -= this->entries[i].shape.getPosition();

		if(point.x < 0 || point.x > this->entries[i].shape.getScale().x*this->dimensions.x) continue;
		if(point.y < 0 || point.y > this->entries[i].shape.getScale().y*this->dimensions.y) continue;
		return i;
	}

	return -1;
}
void GUI::setEntryText(int entry, std::string text)
{
	if(entry >= entries.size() || entry < 0) return;

	entries[entry].text.setString(text);
}
void GUI::setDimensions(sf::Vector2f dimensions)
{
	this->dimensions = dimensions;

	for(auto& entry : entries)
	{
		entry.shape.setSize(dimensions);
		entry.text.setCharacterSize(dimensions.y-style.borderSize-padding);
	}
}
void GUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(!visible) return;

	for(auto entry : this->entries)
	{
		target.draw(entry.shape);
		target.draw(entry.text);
	}
}
void GUI::show()
{
	sf::Vector2f offset(0.0f, 0.0f);

	this->visible = true;

	for(auto& entry : this->entries)
	{
		sf::Vector2f origin = this->getOrigin();
		origin -= offset;
		entry.shape.setOrigin(origin);
		entry.text.setOrigin(origin);
		entry.shape.setPosition(this->getPosition());
		entry.text.setPosition(this->getPosition());

		if(this->horizontal) offset.x += this->dimensions.x;
		else offset.y += this->dimensions.y;
	}

	return;
}
void GUI::hide()
{
	this->visible = false;
}
void GUI::highlight(const int entry)
{
	for(int i = 0; i < entries.size(); ++i)
	{
		if(i == entry) 
		{
			entries[i].shape.setFillColor(style.bodyHighlightColor);
			entries[i].shape.setOutlineColor(style.borderHighlightColor);
			entries[i].text.setColor(style.textHighlightColor);
		}
		else
		{
			entries[i].shape.setFillColor(style.bodyColor);
			entries[i].shape.setOutlineColor(style.borderColor);
			entries[i].text.setColor(style.textColor);
		}
	}
}
std::string GUI::activate(const int entry)
{
	if(entry == -1) return "null";
	return entries[entry].message;
}
std::string GUI::activate(sf::Vector2f mousePos)
{
	int entry = this->getEntry(mousePos);
	return this->activate(entry);
}
