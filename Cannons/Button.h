#pragma once
#ifndef BUTTON_H
#define BUTTON_H
#include <SFML\Graphics.hpp>

struct Button
{
	sf::RectangleShape button;
	sf::Text text;
	bool active;
	bool pressed(sf::Vector2f position);
};

#endif
