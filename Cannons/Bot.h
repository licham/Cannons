#pragma once
#ifndef BOT_H
#define BOT_H
#include <SFML\Graphics.hpp>
#include "Cannon.h"
#include "Shell.h"
#include "Wind.h"
#include "Spline.h"

struct Bot
{
	float pre_power;
	void calculateTraectory(Cannon *cannon, Cannon *enemy, Shell *shell, Wind *wind, sf::RenderWindow *window, Spline *ground);
};

#endif
