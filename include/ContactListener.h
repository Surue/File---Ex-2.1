#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H

#include <SFML/Graphics.hpp>

class MyContactListener : public b2ContactListener {
public:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};#endif