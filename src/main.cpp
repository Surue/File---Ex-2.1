#include <SFML/Graphics.hpp>
#include <iostream>
#include <Box2D/Box2D.h>
#include "PhysicalShape.h"
#include "PhysicalWorld.h"
#include <string>
#include <fstream>
#include <json.hpp>
using json = nlohmann::json;

#define CIRCLE_RADIUS 50
#define RECT_WIDTH 100
#define RECT_HEIGHT 100

int main() {

	std::ifstream file("../data/SFML_data.json");

	if (!file) {
		std::cout << "Fichier introuvable. Fin du programme\n";
		system("pause");
		return EXIT_FAILURE;
	}

	json j;
	file >> j;

	//SFML - Initialise window
	sf::RenderWindow window(sf::VideoMode(j["width"], j["height"]), "Exercice 2.1");
	window.setFramerateLimit((float)j["framerate"]);

	//Box2D - Initialise world
	b2Vec2 gravity(j["gravity"], j["gravity"]); //normal earth gravity, 9.8 m/s/s straight down!
	PhysicalWorld myWorld(gravity, j["Box2D"]["scale"]);

	float32 timeStep = 1 / (float)j["Box2D"]["framerate"];     //the length of time passed to simulate (seconds)
	int32 velocityIterations = j["Box2D"]["velocity"];   //how strongly to correct velocity
	int32 positionIterations = j["Box2D"]["position"];   //how strongly to correct position

	//Initialise both shape
	Circle circle(50, 50, true, myWorld, CIRCLE_RADIUS);
	Rectangle rectangle(window.getSize().x / 2 - RECT_WIDTH/2, window.getSize().y / 2 - RECT_HEIGHT/2, false, myWorld, RECT_WIDTH, RECT_HEIGHT);
	circle.setFillColor(sf::Color::Green);
	rectangle.setFillColor(sf::Color::Blue);

	float speed = j["speed"];
	bool goingUp = false, goingDown = false, goingLeft = false, goingRight = false;
	while (window.isOpen()) {
		myWorld.getWorld()->Step(timeStep, velocityIterations, positionIterations);
		sf::Event event;
		while (window.pollEvent(event)) {
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
		
		//Move circle
		int velY = 0, velX = 0;
		if (goingUp && circle.getShape().getPosition().y > 0) {
			velY = -1;
		}else if (goingDown && circle.getShape().getPosition().y < window.getSize().y - 2 * circle.getShape().getRadius()) {
			velY = 1;
		}

		if (goingLeft && circle.getShape().getPosition().x > 0) {
			velX = -1;
		}else if (goingRight && circle.getShape().getPosition().x < window.getSize().x - 2 * circle.getShape().getRadius()) {
			velX = 1;
		}
		circle.getBody()->SetLinearVelocity(b2Vec2(velX * speed, velY * speed));

		//Check contact
		if (myWorld.getWorld()->GetContactList()) {
			b2Contact* contact = myWorld.getWorld()->GetContactList();
			if (contact->IsTouching()) {
				circle.setFillColor(sf::Color::Red);
				rectangle.setFillColor(sf::Color::Red);
			}else{
				circle.setFillColor(sf::Color::Green);
				rectangle.setFillColor(sf::Color::Blue);
			}
		}

		//Clear - Draw - Display
		window.clear();
		circle.draw(window);
		rectangle.draw(window);
		window.display();
	}

	//delete myWorld;

	system("pause");
	return EXIT_SUCCESS;
}