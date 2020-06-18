#include "Button.h"

bool Button::pressed(sf::Vector2f position)
{
	if ((position.x > button.getPosition().x - button.getOrigin().x) && (position.x < button.getPosition().x + button.getOrigin().x) && (position.y > button.getPosition().y - button.getOrigin().y) && (position.y < button.getPosition().y + button.getOrigin().y))
		return true;
	else
		return false;
}
