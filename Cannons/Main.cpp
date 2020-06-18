#include <SFML\Graphics.hpp>
#include "Spline.h"
#include "Shell.h"
#include "Cannon.h"
#include "Wind.h"
#include "Bot.h"
#include "Button.h"

sf::RenderWindow *window;
sf::Font textFont;
Spline ground(50);
Cannon cannon1, cannon2;
Shell shell;
Wind wind;
Bot bot;
Button button1, button2;

struct Player
{
	int ID;
	bool cheked;
};

Player player1, player2;

void update()
{
	cannon1.current_power.setSize({ cannon1.power * 50 / 13,5 });
	cannon2.current_power.setSize({ cannon2.power * 50 / 13,5 });
	if (!(shell.active))
	{
		cannon1.updateWheel(ground);
		cannon2.updateWheel(ground);
		player1.cheked ? cannon1.updatePower() : cannon2.updatePower();
	}
	if (shell.active)
	{
		shell.calculatePosition(wind.power, wind.current_power.getRotation());
		if ((!(cannon1.attacked)) && (shell.cannonCollision(&cannon1)))
		{
			cannon1.attacked = true;
			cannon1.current_hp.setSize({ cannon1.hp / 2,5 });
			if (cannon1.hp <= 0)
			{
				sf::Text text;
				text.setFont(textFont);
				text.setColor(sf::Color::Red);
				text.setCharacterSize(70);
				text.setStyle(sf::Text::Italic);
				player2.ID == 2 ? text.setString("Player 2 won!!!") : text.setString("Bot won!!!");
				text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
				text.setPosition(1366 / 2, 768 / 2 - 100);
				window->draw(text);
				window->display();
				player2.ID = 0;
				return;
			}
		}
		if ((!(cannon2.attacked)) && (shell.cannonCollision(&cannon2)))
		{
			cannon2.attacked = true;
			cannon2.current_hp.setSize({ cannon2.hp / 2,5 });
			if (cannon2.hp <= 0)
			{
				sf::Text text;
				text.setFont(textFont);
				text.setColor(sf::Color::Red);
				text.setCharacterSize(70);
				text.setStyle(sf::Text::Italic);
				player2.ID == 2 ? text.setString("Player 1 won!!!") : text.setString("You won!!!");
				text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
				text.setPosition(1366 / 2, 768 / 2 - 100);
				window->draw(text);
				window->display();
				player2.ID = 0;
				return;
			}
		}
	}
	if (shell.collision(&ground, true))
	{
		if (player1.cheked)
		{
			player1.cheked = false;
			player2.cheked = true;
			cannon1.power = 0;
		} 
		else
		{
			player1.cheked = true;
			player2.cheked = false;
			cannon2.power = 0;
		}
		cannon1.attacked = cannon2.attacked = false;
		wind.recalculateWind();
	}
}

void draw()
{
	window->clear(sf::Color::White);
	ground.drawSpline(window);
	cannon1.drawCannon(window);
	cannon2.drawCannon(window);
	wind.drawWind(window);
	shell.drawShell(window);
	window->display();
}

void create()
{
	ground.createSpline(50);
	cannon1.create(100, 20, ground);
	cannon2.create(1200, 30, ground);
	wind.create();
	player1.ID = 1;
	player1.cheked = true;
	player2.ID = -1;
	player2.cheked = false;
}

void menuSelectCreate()
{
	window->clear(sf::Color::White);
	button1.text.setFont(textFont);
	button1.text.setCharacterSize(60);
	button1.text.setColor(sf::Color::Black);
	button1.text.setString("Player vs Bot");
	button1.text.setOrigin(button1.text.getLocalBounds().width / 2, button1.text.getLocalBounds().height / 2);
	button1.text.setPosition(2560 / 2, 200);
	button1.button.setSize({ button1.text.getLocalBounds().width, button1.text.getLocalBounds().height + 50 });
	button1.button.setOrigin(button1.button.getLocalBounds().width / 2, button1.button.getLocalBounds().height / 2);
	button1.button.setPosition(button1.text.getPosition());
	button1.button.setOutlineColor(sf::Color::Black);
	button1.button.setOutlineThickness(2);
	window->draw(button1.button);
	window->draw(button1.text);
	button2.text.setFont(textFont);
	button2.text.setCharacterSize(60);
	button2.text.setColor(sf::Color::Black);
	button2.text.setString("Player vs Player");
	button2.text.setOrigin(button2.text.getLocalBounds().width / 2, button2.text.getLocalBounds().height / 2);
	button2.text.setPosition(2560 / 2, 600);
	button2.button.setSize({ button2.text.getLocalBounds().width, button2.text.getLocalBounds().height + 50 });
	button2.button.setOrigin(button2.button.getLocalBounds().width / 2, button2.button.getLocalBounds().height / 2);
	button2.button.setPosition(button2.text.getPosition());
	button2.button.setOutlineColor(sf::Color::Black);
	button2.button.setOutlineThickness(2);
	window->draw(button2.button);
	window->draw(button2.text);
	window->display();
}


int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 100;
	window = new sf::RenderWindow;
	textFont.loadFromFile("Touch.ttf");
	window->create(sf::VideoMode(2560, 1440), "Cannons!", sf::Style::Fullscreen, settings);
	window->setVerticalSyncEnabled(true);
	create();
	menuSelectCreate();
	while (window->isOpen())
	{
		if ((!(shell.active)) && (player2.ID == 3) && (player2.cheked))
			bot.calculateTraectory(&cannon2, &cannon1, &shell, &wind, window, &ground);
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (player2.ID == -1)
			{
				menuSelectCreate();
				if (event.type == sf::Event::MouseButtonReleased)
				{
					sf::Vector2f position = { (float)event.mouseButton.x,(float)event.mouseButton.y };
					if (button1.pressed(position))
						player2.ID = 3;
					if (button2.pressed(position))
						player2.ID = 2;
				}
			}
			else
			{
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::R)
					{
						create();
						menuSelectCreate();
					}
					if ((!(shell.active)) && (player2.ID != 0))
					{
						if (event.key.code == sf::Keyboard::Right)
						{
							if (player1.cheked)
								cannon1.rect.setRotation(cannon1.rect.getRotation() + 2);
							else
								if (player2.ID == 2)
									cannon2.rect.setRotation(cannon2.rect.getRotation() + 2);
						}
						if (event.key.code == sf::Keyboard::Left)
						{
							if (player1.cheked)
								cannon1.rect.setRotation(cannon1.rect.getRotation() - 2);
							else
								if (player2.ID == 2)
									cannon2.rect.setRotation(cannon2.rect.getRotation() - 2);
						}
						if (event.key.code == sf::Keyboard::Space)
						{
							if (player1.cheked)
								shell.create(cannon1.wheel.getPosition(), 360 - cannon1.rect.getRotation(), cannon1.power, 1);
							else
								if (player2.ID == 2)
								{
									shell.create(cannon2.wheel.getPosition(), 180 - cannon2.rect.getRotation(), cannon2.power, -1);
									shell.active = true;
								}
						}
					}
				}
			}
		}
		if ((player2.ID != 0)&&(player2.ID!=-1))
		{
			update();
			if ((player2.ID != 0) && (player2.ID != -1))
				draw();
		}
	}
	return 0;
}