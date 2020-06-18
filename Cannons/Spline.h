#pragma once
#ifndef SPLINE_H
#define SPLINE_H
#include <vector>
#include <SFML\Graphics.hpp>

class Spline
{
private:
	struct spline_segment
	{
		double a, b, c, d, x;
	};
	std::vector<spline_segment> segments;
	int size;
	void buildSpline();
public:
	Spline(int n);
	void createSpline(int n);
	void resetPoint(sf::Vector2f coordinates, sf::Vector2f pre_coordinates);
	void drawSpline(sf::RenderWindow *window);
	double calculateSpline(double x);
};

#endif