#pragma once
#ifndef WIND_H
#define WIND_H
#include <SFML\Graphics.hpp>

struct Wind
{
	float power;
	sf::Font font;
	sf::Text text;
	sf::RectangleShape current_power;
	sf::CircleShape all_power;
	void drawWind(sf::RenderWindow *window);
	void recalculateWind();
	void create();
};

#endif
