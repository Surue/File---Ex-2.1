#include "PhysicalShape.h"

PhysicalShape::PhysicalShape(int x, int y, bool isDynamic, b2World & world) : x(x), y(y), isDynamic(isDynamic) {
}

PhysicalShape::~PhysicalShape() {
}

Circle::Circle(int x, int y, bool isDynamic, b2World & world, sf::CircleShape & shape) : PhysicalShape(x, y, isDynamic, world), shape(shape) {

	//Shape of circle
	b2CircleShape circleShape;
	circleShape.m_p.Set(x, y);
	circleShape.m_radius = shape.getRadius();

	b2BodyDef circleDef;
	if (isDynamic) {
		circleDef.type = b2_dynamicBody;
	} else {
		circleDef.type = b2_staticBody;
	}
	circleDef.position.Set(0.0f, 4.0f);
	circleBody = world.CreateBody(&circleDef);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	circleBody->CreateFixture(&fixtureDef);
}

Circle::~Circle() {
}

void Circle::draw(sf::RenderWindow & window) {
	window.draw(shape);
}

sf::CircleShape Circle::getShape() {
	return shape;
}

b2Body* Circle::getCircleBody() {
	return circleBody;
}

Rectangle::Rectangle(int x, int y, bool isDynamic, b2World & world, sf::RectangleShape shape) : PhysicalShape(x, y, isDynamic, world), shape(shape) {
}

Rectangle::~Rectangle() {
}

void Rectangle::draw(sf::RenderWindow & window) {
	window.draw(shape);
}

sf::RectangleShape Rectangle::getShape() {
	return shape;
}
