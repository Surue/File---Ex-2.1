#ifndef PHYSICAL_SHAPE_H
#define PHYSICAL_SHAPE_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "PhysicalWorld.h"

class PhysicalShape {
protected:
	float x;
	float y;
	bool isDynamic;
	b2Body* body;
	PhysicalWorld* world;
public:
	PhysicalShape(float, float, bool, PhysicalWorld&);
	~PhysicalShape();

	virtual void draw(sf::RenderWindow&) = 0;
	b2Vec2 pixel2meter(sf::Vector2f);
	float pixel2meter(float);
	sf::Vector2f meter2pixel(b2Vec2);
	float meter2pixel(float);
	b2Body* getBody();
};

class Circle : public PhysicalShape {
private: 
	double radius;
	sf::CircleShape shape;
public:
	Circle(float, float, bool, PhysicalWorld&, float);
	~Circle();

	void setFillColor(sf::Color);
	void draw(sf::RenderWindow&);
	sf::CircleShape getShape();

	b2Contact* contact;
};

class Rectangle : public PhysicalShape {
private:
	sf::RectangleShape shape;
	int width;
	int height;
public:
	Rectangle(float, float, bool, PhysicalWorld&, float, float);
	~Rectangle();

	void setFillColor(sf::Color);
	void draw(sf::RenderWindow&);
	sf::RectangleShape getShape();
};

#endif

