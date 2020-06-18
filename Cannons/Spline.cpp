#include "Spline.h"
#include <random>
#include <time.h>
#include <cmath>

Spline::Spline(int n)
{
	segments.clear();
	srand(time(NULL));
	size = n;
	segments.resize(size);
	segments[0].x = 0;
	segments[0].a = 650;
	for (int i = 1; i < size; i++)
	{
		segments[i].x = 1366 / size * i;
		segments[i].a = segments[i - 1].a - 1366 * 2 / size + rand() % (1366 * 4 / size);
		while ((segments[i].a > 700) || (segments[i].a < 50))
			segments[i].a = segments[i - 1].a - 1366 * 2 / size + rand() % (1366 * 4 / size);
	}
	buildSpline();
}

void Spline::createSpline(int n)
{
	segments.clear();
	srand(time(NULL));
	size = n;
	segments.resize(size);
	segments[0].x = 0;
	segments[0].a = 650;
	for (int i = 1; i < size; i++)
	{
		segments[i].x = 1366 / size * i;
		segments[i].a = segments[i - 1].a - 1366 * 2 / size + rand() % (1366 * 4 / size);
		while ((segments[i].a > 700) || (segments[i].a < 50))
			segments[i].a = segments[i - 1].a - 1366 * 2 / size + rand() % (1366 * 4 / size);
	}
	buildSpline();
}

void Spline::resetPoint(sf::Vector2f coordinates, sf::Vector2f pre_coordinates)
{
	int i = 0;
	while ((i < segments.size()) && (segments[i].x < coordinates.x))
		i++;
	if (i == segments.size())
		i--;
	int top, down;
	if (segments[i].a < segments[i - 1].a)
	{
		top = i;
		down = i - 1;
	}
	else
	{
		top = i - 1;
		down = i;
	}
	abs(coordinates.x - segments[down].x) > (abs(segments[top].x - segments[down].x) / 3) ? segments[top].a += 10 : segments[down].a += 10;
	buildSpline();
}

void Spline::buildSpline()
{
	segments[0].c = 0;
	std::vector<double> alpha(size - 1);
	std::vector<double> beta(size - 1);
	double A, B, C, F, Z;
	for (int i = 1; i < size - 1; i++)
	{
		A = segments[i].x - segments[i - 1].x;
		B = segments[i + 1].x - segments[i].x;
		C = 2 * (A + B);
		F = 6 * ((segments[i + 1].a - segments[i].a) / B - (segments[i].a - segments[i - 1].a) / A);
		Z = A*alpha[i - 1] + C;
		alpha[i] = -B / Z;
		beta[i] = (F - A*beta[i - 1]) / Z;
	}
	segments[size - 1].c = (F - A*beta[size - 2]) / (C + A*alpha[size - 2]);
	for (int i = size - 2; i > 0; i--)
		segments[i].c = alpha[i] * segments[i + 1].c + beta[i];
	alpha.clear();
	beta.clear();
	for (int i = size - 1; i > 0; i--)
	{
		A = segments[i].x - segments[i - 1].x;
		segments[i].d = (segments[i].c - segments[i - 1].c) / A;
		segments[i].b = A*(2 * segments[i].c + segments[i - 1].c) / 6 + (segments[i].a - segments[i - 1].a) / A;
	}
}

void Spline::drawSpline(sf::RenderWindow *window)
{
	sf::Vertex line[2];
	line[0].color = sf::Color::Black;
	line[1].color = sf::Color::Black;
	line[0].position.x = 0;
	line[0].position.y = calculateSpline(0);
	for (int i = 1; i < 1366; i++)
	{
		line[1].position.x = i;
		line[1].position.y = calculateSpline(i);
		window->draw(line, 2, sf::Lines);
		line[0].position = line[1].position;
	}
}

double Spline::calculateSpline(double x)
{
	int i = 0;
	while ((i < size - 1) && (segments[i].x < x))
		i++;
	double dx = x - segments[i].x;
	return segments[i].a + (segments[i].b + (segments[i].c / 2 + segments[i].d * dx / 6) * dx) * dx;
}