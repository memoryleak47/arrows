#include "ArrowShotSkill.hpp"

#include <misc/Debug.hpp>
#include <entity/bullets/SimpleArrow.hpp>
#include <entity/Mob.hpp>

ArrowShotSkill::ArrowShotSkill(const SkillGivethrough& gt)
	: TriggerSkill(gt)
{}

void ArrowShotSkill::onTrigger()
{
	addBullet(new SimpleArrow(getOwner()->getPosition(), GameVector(0.4f, 0.f), getOwner()));
}
