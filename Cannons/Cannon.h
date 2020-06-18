#pragma once
#ifndef CANNON_H
#define CANNON_H
#include <SFML\Graphics.hpp>
#include "Spline.h"

struct Cannon
{
	bool v, attacked;
	float power, hp;
	sf::Clock timer;
	sf::RectangleShape rect;
	sf::CircleShape wheel;
	sf::RectangleShape current_power, max_power, current_hp, max_hp;
	void drawCannon(sf::RenderWindow *window);
	void updatePower();
	void updateWheel(Spline ground);
	void create(float x, float x_or, Spline ground);
};

#endif
