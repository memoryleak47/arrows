#ifndef __ARROWSALVESKILL_CLASS__
#define __ARROWSALVESKILL_CLASS__

class Mob;

#include <skill/game/template/TriggerSkill.hpp>

class ArrowSalveSkill : public TriggerSkill
{
	public:
		ArrowSalveSkill(const SkillGivethrough&);
	protected:
		virtual void onTrigger() override;
};

#endif
