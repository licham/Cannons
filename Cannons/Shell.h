#pragma once
#ifndef SHELL_H
#define SHELL_H
#include <SFML\Graphics.hpp>
#include "Spline.h"
#include "Cannon.h"

struct Shell
{
	bool active;
	sf::CircleShape shell;
	sf::Vector2f previous;
	bool cannonCollision(Cannon *cannon);
	bool collision(Spline *ground, bool deformating);
	void calculatePosition(float wind_power, float wind_angle);
	void drawShell(sf::RenderWindow *window);
	void create(sf::Vector2f position, float angle, float power, int reverse);
};

#endif

