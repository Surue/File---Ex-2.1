#include "PhysicalShape.h"
#include <iostream>

PhysicalShape::PhysicalShape(float x, float y, bool isDynamic, PhysicalWorld & world) : x(x), y(y), isDynamic(isDynamic), world(&world) {
}

PhysicalShape::~PhysicalShape() {
}

b2Vec2 PhysicalShape::pixel2meter(sf::Vector2f vectP) {
	b2Vec2 vectM;
	vectM.x = vectP.x * world->getScale();
	vectM.y = vectP.y * world->getScale();
	return vectM;
}

float PhysicalShape::pixel2meter(float pixel) {
	return pixel* world->getScale();
}

sf::Vector2f PhysicalShape::meter2pixel(b2Vec2 vectM) {
	sf::Vector2f vectP;
	vectP.x = vectM.x / world->getScale();
	vectP.y = vectM.y / world->getScale();
	return vectP;
}

float PhysicalShape::meter2pixel(float meter) {
	return meter / world->getScale();
}

b2Body * PhysicalShape::getBody() {
	return body;
}

Circle::Circle(float x, float y, bool isDynamic, PhysicalWorld & world, float radius) : PhysicalShape(x, y, isDynamic, world) {
	//SFML Shape
	shape = sf::CircleShape(radius);
	shape.setPosition(x, y);

	//Box2D Shape
	b2CircleShape circleShape;
	circleShape.m_radius = pixel2meter(shape.getRadius());
	circleShape.m_p = pixel2meter(sf::Vector2f(radius, radius));

	//Body
	b2BodyDef circleDef;
	if (isDynamic) {
		circleDef.type = b2_dynamicBody;
	} else {
		circleDef.type = b2_staticBody;
	}
	circleDef.position = pixel2meter(shape.getPosition());
	body = this->world->getWorld()->CreateBody(&circleDef);

	//Fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	body->CreateFixture(&fixtureDef);
}

Circle::~Circle() {
	//delete body;
}

void Circle::setFillColor(sf::Color color) {
	shape.setFillColor(color);
}

void Circle::draw(sf::RenderWindow & window) {
	shape.setPosition(meter2pixel(body->GetPosition()));
	window.draw(shape);
}

sf::CircleShape Circle::getShape() {
	return shape;
}

Rectangle::Rectangle(float x, float y, bool isDynamic, PhysicalWorld & world, float width, float height) : PhysicalShape(x, y, isDynamic, world) {
	//SFML Shape
	shape = sf::RectangleShape(sf::Vector2f(width, height));
	shape.setPosition(x, y);

	//Body
	b2BodyDef rectangleDef;
	if (isDynamic) {
		rectangleDef.type = b2_dynamicBody;
	}
	else {
		rectangleDef.type = b2_staticBody;
	}
	rectangleDef.position = pixel2meter(shape.getPosition());
	body = this->world->getWorld()->CreateBody(&rectangleDef);

	//Fixture
	b2PolygonShape rectangleBox;
	rectangleBox.SetAsBox(pixel2meter(width/2.f), pixel2meter(height / 2.f), pixel2meter(sf::Vector2f(width/2, height/2)), 0.f);
	body->CreateFixture(&rectangleBox, 0.f);
}

Rectangle::~Rectangle() {
}

void Rectangle::setFillColor(sf::Color color) {
	shape.setFillColor(color);
}

void Rectangle::draw(sf::RenderWindow & window) {
	shape.setPosition(meter2pixel(body->GetPosition()));
	window.draw(shape);
}

sf::RectangleShape Rectangle::getShape() {
	return shape;
}
