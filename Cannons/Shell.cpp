#include "Shell.h"
#include <random>
#include <time.h>
#include <cmath>

bool Shell::cannonCollision(Cannon * cannon)
{
	srand(time(NULL));
	if (active)
	{
		sf::Vector2f position = shell.getPosition();
		if ((position.x > cannon->rect.getGlobalBounds().left) && (position.x<cannon->rect.getGlobalBounds().left + cannon->rect.getGlobalBounds().width) && (position.y>cannon->rect.getGlobalBounds().top) && (position.y < cannon->rect.getGlobalBounds().top + cannon->rect.getGlobalBounds().height))
		{
			cannon->hp -= rand() % 20;
			return true;
		}
	}
	return false;
}

bool Shell::collision(Spline *ground, bool deformating)
{
	if (active)
	{
		if ((shell.getPosition().x > 1365) || (shell.getPosition().x < 0) || (shell.getPosition().y > 767))
		{
			active = false;
			return true;
		}
		else
			if (shell.getPosition().y + 10 > ground->calculateSpline(shell.getPosition().x))
			{
				if (deformating)
					ground->resetPoint(shell.getPosition(), previous);
				active = false;
				return true;
			}
	}
	return false;
}

void Shell::calculatePosition(float wind_power, float wind_angle)
{
	if (active)
	{
		sf::Vector2f bufer = previous;
		previous = shell.getPosition();
		shell.setPosition(shell.getPosition().x * 2 - bufer.x + wind_power * 0.01 * cos(wind_angle * (float)3.14 / (float)180.), shell.getPosition().y * 2 - bufer.y + 0.1 + wind_power * 0.01 * sin(wind_angle * (float)3.14 / (float)180.));
	}
}

void Shell::drawShell(sf::RenderWindow * window)
{
	if (active)
		window->draw(shell);
}

void Shell::create(sf::Vector2f position, float angle, float power, int reverse)
{
	shell.setRadius(10);
	shell.setPointCount(32);
	shell.setOrigin(10, 10);
	previous = { position.x + 40 * cos(angle * (float)3.14 / (float)180.) - 10 * reverse * sin(angle * (float)3.14 / (float)180.),position.y - 40 * sin(angle * (float)3.14 / (float)180.) - 10 * reverse * cos(angle * (float)3.14 / (float)180.) };
	shell.setPosition(previous.x + power*cos(angle * (float)3.14 / (float)180.), previous.y - power*sin(angle * (float)3.14 / (float)180.));
	shell.setOutlineThickness(1);
	shell.setOutlineColor(sf::Color::Black);
	shell.setFillColor(sf::Color::Color(54, 54, 54));
	active = true;
}
