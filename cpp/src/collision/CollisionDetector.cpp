#include "CollisionDetector.hpp"

#include "../misc/Debug.hpp"

void CollisionDetector::addCollisionsBetween(Entity* e1, Entity* e2, std::vector<CollisionEvent*>* events, float timeLeft)
{
	if (e1->getBody()->getBodyType() == BodyType::RECT && e2->getBody()->getBodyType() == BodyType::RECT)
	{
		if (dynamic_cast<const RectBody*>(e1->getBody())->isEven() && dynamic_cast<const RectBody*>(e2->getBody())->isEven())
		{
			addCollisionsBetweenEvenRects(e1, e2, events, timeLeft);
		}
		else
		{
			Debug::warn("CollisionDetector::addCollisionsBetween: TODO");
		}
	}
	else
	{
		Debug::warn("CollisionDetector::addCollisionsBetween: TODO");
	}
}


// private function
int getNextIndex(const std::vector<float>& floats)
{
	int spot = 0;
	for (unsigned int i = 1; i < floats.size(); i++)
	{
		if (floats[i] < floats[spot])
		{
			spot = i;
		}
	}
	return spot;
}

// private function
std::pair<std::vector<float>, std::vector<bool>> getPair(float posX1, float posY1, float sizeX1, float sizeY1, float speedX, float speedY, float posX2, float posY2, float sizeX2, float sizeY2, float timeLeft)
{
	std::vector<float> floats;
	std::vector<bool> bools;

	// x
	float a = ((posX1 - sizeX1/2.f) - (posX2 + sizeX2/2.f)) / -speedX;
	if (a >= 0.f && a <= timeLeft)
	{
		floats.push_back(a);
		bools.push_back(true);
	}
	a = ((posX2 - sizeX2/2.f) - (posX1 + sizeX1/2.f)) / speedX;
	if (a >= 0.f && a <= timeLeft)
	{
		floats.push_back(a);
		bools.push_back(true);
	}

	// y
	a = ((posY1 - sizeY1/2.f) - (posY2 + sizeY2/2.f)) / -speedY;
	if (a >= 0.f && a <= timeLeft)
	{
		floats.push_back(a);
		bools.push_back(false);
	}
	a = ((posY2 - sizeY2/2.f) - (posY1 + sizeY1/2.f)) / speedY;
	if (a >= 0.f && a <= timeLeft)
	{
		floats.push_back(a);
		bools.push_back(false);
	}

	return std::pair<std::vector<float>, std::vector<bool>>(floats, bools);
}

void CollisionDetector::addCollisionsBetweenEvenRects(Entity* e1, Entity* e2, std::vector<CollisionEvent*>* events, float timeLeft)
{
	const RectBody* b1 = dynamic_cast<const RectBody*>(e1->getBody());
	const RectBody* b2 = dynamic_cast<const RectBody*>(e2->getBody());

	float posX1 = b1->getPosition().getX();
	float posY1 = b1->getPosition().getY();
	float sizeX1 = b1->getSize().getX();
	float sizeY1 = b1->getSize().getY();

	// speed subtraction
	float speedX = b1->getSpeed().getX() - b2->getSpeed().getX();
	float speedY = b1->getSpeed().getY() - b2->getSpeed().getY();

	float posX2 = b2->getPosition().getX();
	float posY2 = b2->getPosition().getY();
	float sizeX2 = b2->getSize().getX();
	float sizeY2 = b2->getSize().getY();

	switch (Entity::getCollisionTypeBetween(e1, e2))
	{
		case CollisionType::SOLID:
		{
			// getestet
			bool xCol = ((posX1 + sizeX1/2.f) > (posX2 - sizeX2/2.f)) && ((posX2 + sizeX2/2.f) > (posX1 - sizeX1/2.f));
			bool yCol = ((posY1 + sizeY1/2.f) > (posY2 - sizeY2/2.f)) && ((posY2 + sizeY2/2.f) > (posY1 - sizeY1/2.f));

			std::pair<std::vector<float>, std::vector<bool>> pair = getPair(posX1, posY1, sizeX1, sizeY1, speedX, speedY, posX2, posY2, sizeX2, sizeY2, timeLeft);
			std::vector<float> floats = pair.first;
			std::vector<bool> bools = pair.second;

			if (xCol && yCol)
			{
				CollisionEvent* ev = new CollisionEvent(e1, e2, timeLeft);
				Debug::func("detected event(1): " + ev->toString());
				events->push_back(ev);
			}
			bool wasColliding = (xCol && yCol);
			while (floats.size() > 0)
			{
				int index = getNextIndex(floats);
				float time = floats[index];

				if (bools[index])
				{
					xCol = !xCol;
				}
				else
				{
					yCol = !yCol;
				}

				floats.erase(floats.begin() + index);
				bools.erase(bools.begin() + index);

				if (wasColliding != (xCol && yCol))
				{
					CollisionEvent* ev = new CollisionEvent(e1, e2, timeLeft-time);
					events->push_back(ev);
					Debug::func("detected event(2): " + ev->toString());
					wasColliding = (xCol && yCol);
				}
			}
			break;
		}
		case CollisionType::IGNORE:
		{
			Debug::warn("TODO ignore collision");
			break;
		}
		default:
		{
			Debug::error("CollisionDetector::addCollisionsBetweenEvenRects: unknown CollisionType");
			break;
		}
	}
}
