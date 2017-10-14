#ifndef PHYSICAL_WORLD_H
#define PHYSICAL_WORLD_H

#include <Box2D\Box2D.h>
#include "json.hpp"
using json = nlohmann::json;

class PhysicalWorld {
private:
	b2World* world;
	float scale;
public:
	PhysicalWorld(b2Vec2, float);
	~PhysicalWorld();
	
	b2World* getWorld() const;
	float getScale() const;
};
#endif