#include "PhysicsHandler.hpp"

#include <misc/Global.hpp>
#include <math/game/GameVector.hpp>
#include <entity/Entity.hpp>

void PhysicsHandler::handlePhysics(Entity* e1, Entity* e2, const GameVector& collisionPoint)
{
	Debug::funcOn("PhysicsHandler::handlePhysics(" + e1->toString() + ", " + e2->toString() + ")");

	float ms1 = 0.f;

	if (e1->isStatic())
	{
		if (e2->isStatic())
		{
			Debug::warn("PhysicsHandler::handlePhysics(): e1 and e2 are static");
			return;
		}
		else
		{
			ms1 = 1.f;
		}
	}
	else
	{
		if (not e2->isStatic())
		{
			ms1 = e1->getMass() / (e1->getMass() + e2->getMass());
		}
	}
	GameVector v1 = e1->getSpeedAt(collisionPoint);

	float sponge = Entity::getSpongeBetween(e1, e2);

	e1->reactToCollision(ms1, e2->getSpeedAt(collisionPoint), collisionPoint, sponge);
	e2->reactToCollision(1.f - ms1, v1, collisionPoint, sponge);

	Debug::funcOff("PhysicsHandler::handlePhysics(" + e1->toString() + ", " + e2->toString() + ")");
}
