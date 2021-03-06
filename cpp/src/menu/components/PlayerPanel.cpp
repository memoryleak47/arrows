#include "PlayerPanel.hpp"

#include <misc/Debug.hpp>
#include <core/Screen.hpp>
#include "PlayerPanelsAvatarIcon.hpp"
#include "PlayerPanelsSkillIcon.hpp"
#include "PlayerPanelsItemIcon.hpp"
#include <player/LobbyPlayer.hpp>
#include <network/packets/LockPacket.hpp>
#include <network/packets/LoginPacket.hpp>
#include <menu/menues/LobbyMenu.hpp>
#include <menu/components/TeamPanel.hpp>

PlayerPanel::PlayerPanel(LobbyPlayer* p, LobbyMenu* m, TeamPanel* c, const PixelRect& r)
	: Panel(c, r), player(p), lobby(m)
{
	addComponent(new PlayerPanelsAvatarIcon(getPlayer(), getLobbyMenu(), this, PixelRect(0,0,AVATAR_ICON_SIZE,AVATAR_ICON_SIZE)));

	// SkillIcons
	addComponent(new PlayerPanelsSkillIcon(0, getPlayer(), getLobbyMenu(), this,  PixelRect(0 ,45,SKILL_ICON_SIZE,SKILL_ICON_SIZE)));
	addComponent(new PlayerPanelsSkillIcon(1, getPlayer(), getLobbyMenu(), this,  PixelRect(15,45,SKILL_ICON_SIZE,SKILL_ICON_SIZE)));
	addComponent(new PlayerPanelsSkillIcon(2, getPlayer(), getLobbyMenu(), this,  PixelRect(30,45,SKILL_ICON_SIZE,SKILL_ICON_SIZE)));
	addComponent(new PlayerPanelsSkillIcon(3, getPlayer(), getLobbyMenu(), this,  PixelRect(45,45,SKILL_ICON_SIZE,SKILL_ICON_SIZE)));

	// ItemIcons
	addComponent(new PlayerPanelsItemIcon(0, getPlayer(), getLobbyMenu(), this, PixelRect(45,0, ITEM_ICON_SIZE, ITEM_ICON_SIZE)));
	addComponent(new PlayerPanelsItemIcon(1, getPlayer(), getLobbyMenu(), this, PixelRect(45,15,ITEM_ICON_SIZE, ITEM_ICON_SIZE)));
	addComponent(new PlayerPanelsItemIcon(2, getPlayer(), getLobbyMenu(), this, PixelRect(45,30,ITEM_ICON_SIZE, ITEM_ICON_SIZE)));
}

void PlayerPanel::render() const
{
	Panel::render();
	if (getPlayer() != nullptr && getPlayer()->getLockPacket()->isLocked())
	{
		Screen::drawRect(PixelRect(getAbsoluteRect().getPosition().x-2, getAbsoluteRect().getPosition().y-2, getRelativeRect().getSize().x+4, getRelativeRect().getSize().y+4), sf::Color::Yellow);
	}
	if (getPlayer() == getLobbyMenu()->getLocalPlayer())
	{
		Screen::drawRect(PixelRect(getAbsoluteRect().getPosition().x-1, getAbsoluteRect().getPosition().y-1, getRelativeRect().getSize().x+2, getRelativeRect().getSize().y+2), sf::Color::Blue);
	}
	Screen::drawText(getPlayer()->getLoginPacket()->getName(), PixelVector(getAbsoluteRect().getPosition().x, getAbsoluteRect().getPosition().y + 72), sf::Color::White);
	Screen::drawText("" + getPlayer()->getLoginPacket()->getRank(), PixelVector(getAbsoluteRect().getPosition().x, getAbsoluteRect().getPosition().y + 10), sf::Color::White);
}

LobbyPlayer* PlayerPanel::getPlayer() const
{
	return player;
}

LobbyMenu* PlayerPanel::getLobbyMenu() const
{
	return lobby;
}
