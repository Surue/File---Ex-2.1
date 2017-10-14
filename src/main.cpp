#include <SFML/Graphics.hpp>
#include <iostream>

#include <Box2D/Box2D.h>
#include "PhysicalShape.h"

int main() {

	b2Vec2 gravity(0.f, 0.f); //normal earth gravity, 9.8 m/s/s straight down!

	b2World* myWorld = new b2World(gravity);
	
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	window.setFramerateLimit(60.f);

	float32 timeStep = 1 / 60.0;     //the length of time passed to simulate (seconds)
	int32 velocityIterations = 8;   //how strongly to correct velocity
	int32 positionIterations = 3;   //how strongly to correct position

	//Circle
	sf::CircleShape circle(50.f);
	circle.setFillColor(sf::Color::Green);

	Circle circleNew(0, 0, true, *myWorld, circle);
	
	/*b2CircleShape circleShape;
	circleShape.m_p.Set(circle.getPosition().x, circle.getPosition().y);
	circleShape.m_radius = 50.f;

	b2BodyDef circleDef;
	circleDef.type = b2_dynamicBody;
	circleDef.position.Set(0.0f, 4.0f);
	b2Body* circleBody = myWorld->CreateBody(&circleDef);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	circleBody->CreateFixture(&fixtureDef); */
	
	//Rect
	sf::RectangleShape rectangle(sf::Vector2f(100, 100));
	rectangle.setFillColor(sf::Color::Blue);
	rectangle.setPosition(window.getSize().x/2 - rectangle.getSize().x/2, window.getSize().y/2 - rectangle.getSize().y/2);

	b2BodyDef rectangleBodyDef;
	rectangleBodyDef.position.Set(rectangle.getPosition().x, rectangle.getPosition().y);
	rectangleBodyDef.type = b2_staticBody;

	b2Body* rectangleBody = myWorld->CreateBody(&rectangleBodyDef);
	b2PolygonShape rectangleBox;
	rectangleBox.SetAsBox(50.f, 50.f);
	rectangleBody->CreateFixture(&rectangleBox, 0.0f);


	float speed = 5.0f;
	bool goingUp = false, goingDown = false, goingLeft = false, goingRight = false;
	while (window.isOpen())
	{
		myWorld->Step(timeStep, velocityIterations, positionIterations);
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Up:
					goingUp = true;
					break;

				case sf::Keyboard::Down:
					goingDown = true;
					break;

				case sf::Keyboard::Left:
					goingLeft = true;
					break;

				case sf::Keyboard::Right:
					goingRight = true;
					break;

				case sf::Keyboard::Escape:
					window.close();
					break;
				}
				break;

			case sf::Event::KeyReleased:
				switch (event.key.code) {
				case sf::Keyboard::Up:
					goingUp = false;
					break;

				case sf::Keyboard::Down:
					goingDown = false;
					break;

				case sf::Keyboard::Left:
					goingLeft = false;
					break;

				case sf::Keyboard::Right:
					goingRight = false;
					break;
				}
				break;
			}
		}
		
		int velY = 0, velX = 0;
		if (goingUp && circleNew.getCircleBody()->GetPosition().y > 0) {
			std::cout << "up\n";
			std::cout << circleNew.getShape().getPosition().y << "\n";
			velY = -1000;
		}else if (goingDown && circleNew.getCircleBody()->GetPosition().y < window.getSize().y - 2* circleNew.getCircleBody()->GetFixtureList()->GetShape()->m_radius) {
			velY = 1000;
		}

		if (goingLeft && circleNew.getCircleBody()->GetPosition().x > 0) {
			velX = -1000;
		}else if (goingRight && circleNew.getCircleBody()->GetPosition().x < window.getSize().x - 2 * circleNew.getCircleBody()->GetFixtureList()->GetShape()->m_radius) {
			velX = 1000;
		}
		
		if (myWorld->GetContactList()) {
			circleNew.getShape().setFillColor(sf::Color::Red);
			rectangle.setFillColor(sf::Color::Red);
		} else {
			circleNew.getShape().setFillColor(sf::Color::Green);
			rectangle.setFillColor(sf::Color::Blue);
		}
		circleNew.getCircleBody()->SetLinearVelocity(b2Vec2(velX, velY));
		circleNew.getShape().setPosition(circleNew.getCircleBody()->GetPosition().x, circleNew.getCircleBody()->GetPosition().y);
		rectangle.setPosition(rectangleBody->GetPosition().x, rectangleBody->GetPosition().y);

		window.clear();
		circleNew.draw(window);
		//window.draw(circleNew.getShape());
		window.draw(rectangle);
		window.display();
	}
	delete myWorld;

	system("pause");
	return 0;
}