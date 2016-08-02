#include "CollisionEvent.hpp"

#include "../misc/Converter.hpp"

CollisionEvent::CollisionEvent(Entity* e1, Entity* e2, float timeUntilFrameEnds, CollisionStatus status)
	: entity1(e1), entity2(e2), timeUntilFrameEnds(timeUntilFrameEnds), status(status)
{}

Entity* CollisionEvent::getEntity1() const
{
	return entity1;
}

Entity* CollisionEvent::getEntity2() const
{
	return entity2;
}

float CollisionEvent::getTimeUntilFrameEnds() const
{
	return timeUntilFrameEnds;
}

std::string CollisionEvent::toString() const
{
	return "(e1=" + entity1->toString() + " e2=" + entity2->toString() + " time=" + Converter::floatToString(timeUntilFrameEnds) + ")";
}

CollisionStatus CollisionEvent::getStatus() const
{
	return status;
}
