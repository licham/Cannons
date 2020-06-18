#include "Wind.h"
#include <random>
#include <time.h>

void Wind::drawWind(sf::RenderWindow * window)
{
	window->draw(all_power);
	window->draw(current_power);
	window->draw(text);
}

void Wind::recalculateWind()
{
	power = rand() % 5;
	current_power.setSize({ power * 5,5 });
	current_power.setRotation(rand() % 360);
}

void Wind::create()
{
	srand(time(NULL));
	all_power.setRadius(25);
	all_power.setPointCount(32);
	all_power.setOrigin(all_power.getRadius(), all_power.getRadius());
	all_power.setPosition(1366 / 2, 200);
	all_power.setOutlineColor(sf::Color::Black);
	all_power.setOutlineThickness(1);
	current_power.setOrigin({ 0,2.5 });
	current_power.setPosition(all_power.getPosition());
	recalculateWind();
	current_power.setFillColor(sf::Color::Blue);
	current_power.setOutlineColor(sf::Color::Black);
	current_power.setOutlineThickness(1);
	font.loadFromFile("Touch.ttf");
	text.setFont(font);
	text.setColor(sf::Color::Blue);
	text.setCharacterSize(30);
	text.setString("Wind");
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setPosition(1366 / 2, 150);
}
