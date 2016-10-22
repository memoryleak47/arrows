#include "PlayerPanelsSkillIcon.hpp"

#include <misc/Global.hpp>
#include <menu/MenuList.hpp>
#include <core/Main.hpp>
#include <player/property/skill/Skill.hpp>
#include <menu/menues/ChoosePlayerPropertyMenu.hpp>
#include <menu/menues/LobbyMenu.hpp> // for SKILL_PHASE
#include <network/packets/SkillUserPacket.hpp>
#include <player/LobbyPlayer.hpp>
#include <network/packets/AvatarUserPacket.hpp>

PlayerPanelsSkillIcon::PlayerPanelsSkillIcon(int n, LobbyPlayer* p, LobbyMenu* m, ComponentContainer* c, const PixelRect& r) : PlayerPanelsIcon(p, m, c, r), number(n)
{}

int PlayerPanelsSkillIcon::getChoosePhase() const
{
	return SKILL_PHASE;
}

void PlayerPanelsSkillIcon::onClick(int mouseButton)
{
	if (isChoosable())
	{
		const std::vector<Skill*>& skills = Skill::getAllSkillsByAvatarID(getLobbyMenu()->getLocalPlayer()->getAvatarUserPacket()->getAvatarID());
		std::vector<PlayerProperty*> tmp;
		for (unsigned int i = 0; i < skills.size(); i++)
		{
			tmp.push_back(skills[i]);
		}
		Main::getMenuList()->addMenu(new ChoosePlayerPropertyMenu(getLobbyMenu(), new SkillUserPacket(*getLobbyMenu()->getLocalPlayer()->getSkillUserPacket()), tmp));
	}
}

TextureID PlayerPanelsSkillIcon::getTextureID() const
{
	if ((getPlayer()->getSkillUserPacket() == NULL) ||
	    (getPlayer()->getSkillUserPacket()->getPlayerProperties()[number] == NULL))
	{
		return VOID_ICON_GID;
	}
	return getPlayer()->getSkillUserPacket()->getPlayerProperties()[number]->getIconTextureID();
}
