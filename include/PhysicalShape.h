#ifndef PHYSICAL_SHAPE_H
#define PHYSICAL_SHAPE_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class PhysicalShape {
private:
	int x;
	int y;
	bool isDynamic;
public:
	PhysicalShape(int, int, bool, b2World&);
	~PhysicalShape();

	virtual void draw(sf::RenderWindow&) = 0;
};

class Circle : public PhysicalShape {
private: 
	double radius;
	sf::CircleShape shape;
	b2Body* circleBody;
public:
	Circle(int, int, bool, b2World&, sf::CircleShape&);
	~Circle();

	void draw(sf::RenderWindow&);
	sf::CircleShape getShape();
	b2Body* getCircleBody();
};

class Rectangle : public PhysicalShape {
private:
	sf::RectangleShape shape;
public:
	Rectangle(int, int, bool, b2World&, sf::RectangleShape);
	~Rectangle();

	void draw(sf::RenderWindow&);
	sf::RectangleShape getShape();
};

#endif

