#include "ArrowShotSkill.hpp"

extern int ARROWSHOTSKILL_SID;
extern int ARCHER_AID;

char ArrowShotSkill::getID() const
{
	return ARROWSHOTSKILL_SID;
}

std::string ArrowShotSkill::getDescription() const
{
	return "shoots an arrow";
}

char ArrowShotSkill::getAvatarID() const
{
	return ARCHER_AID;
}

GraphicsID ArrowShotSkill::getIconGraphicsID() const
{
	return ARROWSHOTSKILL_ICON_GID;
}

Skill* ArrowShotSkill::clone() const
{
	return new ArrowShotSkill();
}
