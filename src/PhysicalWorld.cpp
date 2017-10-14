#include "PhysicalWorld.h"

PhysicalWorld::PhysicalWorld(b2Vec2 gravity, float scale) {
	this->world = new b2World(gravity);
	this->scale = 1 / scale;
}

PhysicalWorld::~PhysicalWorld() {
	delete world;
}

float PhysicalWorld::getScale() const {
	return scale;
}

b2World* PhysicalWorld::getWorld() const {
	return world;
}
