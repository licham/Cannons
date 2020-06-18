#include "Cannon.h"

void Cannon::drawCannon(sf::RenderWindow * window)
{
	/*sf::Sprite sprite;
	sprite.setTexture(*rect.getTexture());
	sprite.setOrigin(rect.getOrigin());
	sprite.setPosition(rect.getPosition());
	sprite.setRotation(rect.getRotation());
	window->draw(sprite);*/
	window->draw(rect);
	window->draw(wheel);
	window->draw(max_power);
	window->draw(current_power);
	window->draw(max_hp);
	window->draw(current_hp);
}

void Cannon::updatePower()
{
	if (power >= 13)
		v = false;
	if (power <= 0)
		v = true;
	v ? power += 0.3 : power -= 0.3;
}

void Cannon::updateWheel(Spline ground)
{
	if (ground.calculateSpline(wheel.getPosition().x) < ground.calculateSpline(wheel.getPosition().x - 1))
	{
		wheel.move(-1, 0);
		wheel.rotate(1);
	}
	else
		if (ground.calculateSpline(wheel.getPosition().x) < ground.calculateSpline(wheel.getPosition().x + 1))
		{
			wheel.move(1, 0);
			wheel.rotate(-1);
		}
	wheel.setPosition(wheel.getPosition().x, ground.calculateSpline(wheel.getPosition().x));
	sf::Vector2f position;
	for (int i = 0; i < wheel.getPointCount(); i++)
	{
		position.x = wheel.getPosition().x - wheel.getOrigin().x + wheel.getPoint(i).x;
		position.y = wheel.getPosition().y - wheel.getOrigin().y + wheel.getPoint(i).y;
		if (position.y > ground.calculateSpline(position.x))
			wheel.move(0, ground.calculateSpline(position.x) - position.y);
	}
	rect.setPosition(wheel.getPosition());
	max_power.setPosition(wheel.getPosition().x - 20, wheel.getPosition().y - 40);
	current_power.setPosition(max_power.getPosition());
	max_hp.setPosition(wheel.getPosition().x - 20, wheel.getPosition().y - 50);
	current_hp.setPosition(max_hp.getPosition());
}

void Cannon::create(float x, float x_or, Spline ground)
{
	rect.setRotation(0);
	v = true;
	attacked = false;
	hp = 100;
	sf::Vector2f position;
	wheel.setPointCount(32);
	wheel.setRadius(11);
	wheel.setOrigin(11, 11);
	wheel.setPosition(x, ground.calculateSpline(x));
	for (int i = 0; i < wheel.getPointCount(); i++)
	{
		position.x = wheel.getPosition().x - wheel.getOrigin().x + wheel.getPoint(i).x;
		position.y = wheel.getPosition().y - wheel.getOrigin().y + wheel.getPoint(i).y;
		if (position.y > ground.calculateSpline(position.x))
			wheel.move(0, ground.calculateSpline(position.x) - position.y);
	}
	wheel.setOutlineThickness(1);
	wheel.setOutlineColor(sf::Color::Black);
	wheel.setFillColor(sf::Color::Color(255, 106, 106));
	rect.setSize({ 50,20 });
	rect.setOrigin(x_or, 20);
	rect.setPosition(wheel.getPosition());
	rect.setOutlineThickness(1);
	rect.setOutlineColor(sf::Color::Black);
	rect.setFillColor(sf::Color::Color(79, 79, 79));
	sf::Texture texture;
	texture.loadFromFile("Cannon.png");
	rect.setTexture(&texture);
	max_power.setPosition(wheel.getPosition().x - 20, wheel.getPosition().y - 40);
	max_power.setSize({ 50,5 });
	max_power.setOutlineThickness(1);
	max_power.setOutlineColor(sf::Color::Black);
	current_power.setPosition(max_power.getPosition());
	current_power.setSize({ 0,5 });
	current_power.setOutlineThickness(1);
	current_power.setOutlineColor(sf::Color::Black);
	current_power.setFillColor(sf::Color::Red);
	max_hp.setPosition(wheel.getPosition().x - 20, wheel.getPosition().y - 50);
	max_hp.setSize({ 50,5 });
	max_hp.setOutlineThickness(1);
	max_hp.setOutlineColor(sf::Color::Black);
	current_hp.setPosition(max_hp.getPosition());
	current_hp.setSize({ 50,5 });
	current_hp.setOutlineThickness(1);
	current_hp.setOutlineColor(sf::Color::Black);
	current_hp.setFillColor(sf::Color::Green);
}
