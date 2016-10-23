#ifndef __MOB_CLASS__
#define __MOB_CLASS__

class Body;
class Controller;
class CompressBuffer;
class View;

#include "ImpactfulDynamicEntity.hpp"
#include <string>

class Mob : public ImpactfulDynamicEntity
{
	public:
		Mob(Body*, Controller*);
		Mob(CompressBuffer*);
		virtual ~Mob(); // deletes controller

		// compress
		std::string getCompressString() const override;
		virtual void tick() override;
		virtual EntityType getEntityType() const override;
		virtual void renderBar(const View&) const = 0;
		virtual void actionGoLeft();
		virtual void actionGoRight();
		virtual void actionJump();
		virtual float getMass() const override;
	protected:
		virtual float getMaxXSpeed() const;
		virtual void optSetSkillEnabled(int, bool); // called from applyActions(); only used in GamePlayer
		Controller* getController() const;

		Controller* controller;
	private:
		void applyActions();

};

#endif
