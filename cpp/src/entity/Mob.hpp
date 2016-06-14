#ifndef __MOB_CLASS__
#define __MOB_CLASS__

#include "Entity.hpp"

class Mob : public Entity
{
	public:
		Mob(Body*);
		virtual ~Mob() {}
		virtual EntityType getEntityType() override;
		virtual void renderBar(const View&) const = 0;
		virtual void actionGoLeft();
		virtual void actionGoRight();
		virtual void actionJump();
	protected:
		virtual float getMaxXSpeed() { return 0.3f; }
};

#endif
