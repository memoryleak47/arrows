#ifndef __ARROWSHOTSKILL_CLASS__
#define __ARROWSHOTSKILL_CLASS__

class Mob;

#include <skill/game/template/TriggerSkill.hpp>

class ArrowShotSkill : public TriggerSkill
{
	public:
		ArrowShotSkill(const SkillGivethrough&);
	protected:
		virtual void onTrigger() override;
};

#endif
