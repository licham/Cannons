#include "Bot.h"
#include <iostream>

void draw(Cannon * cannon, Cannon *enemy, Wind * wind, sf::RenderWindow *window, Spline *ground)
{
	window->clear(sf::Color::White);
	ground->drawSpline(window);
	cannon->drawCannon(window);
	enemy->drawCannon(window);
	wind->drawWind(window);
	window->display();
}

void Bot::calculateTraectory(Cannon * cannon, Cannon *enemy, Shell * shell, Wind * wind, sf::RenderWindow *window, Spline *ground)
{
	for (int i = 0; i <= 360; i += 2)
	{
		for (float power = 0; power <= 13; power += 0.3)
		{
			shell->create(cannon->wheel.getPosition(), i, power, -1);
			while (shell->active)
			{
				shell->calculatePosition(wind->power, wind->current_power.getRotation());
				if (shell->collision(ground, false))
					shell->active = false;
				if (hypot(shell->shell.getPosition().x - enemy->rect.getPosition().x, shell->shell.getPosition().y - enemy->rect.getPosition().y) < 10)
				{
					while (cannon->rect.getRotation() != 180 - i)
					{
						cannon->updatePower();
						cannon->current_power.setSize({ cannon->power * 50 / 13,5 });
						if (cannon->rect.getRotation() > 180 - i)
							cannon->rect.rotate(-2);
						else
							if (cannon->rect.getRotation() < 180 - i)
								cannon->rect.rotate(+2);
						draw(cannon, enemy, wind, window, ground);
					}
					while (cannon->power != power)
					{
						cannon->updatePower();
						cannon->current_power.setSize({ cannon->power * 50 / 13,5 });
						draw(cannon, enemy, wind, window, ground);
					}
					pre_power = power;
					shell->create(cannon->wheel.getPosition(), 180 - cannon->rect.getRotation(), cannon->power, -1);
					return;
				}
			}
		}
	}
	shell->create(cannon->wheel.getPosition(), 180 - cannon->rect.getRotation(), pre_power, -1);
}


