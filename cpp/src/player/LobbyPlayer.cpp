#include "LobbyPlayer.hpp"

#include "../misc/Debug.hpp"
#include "../core/Main.hpp"

LobbyPlayer::LobbyPlayer(LobbyPlayer* player)
	: ip(player->ip)
{
	lockPacket = new LockUserPacket(*player->lockPacket);
	teamPacket = new TeamUserPacket(*player->teamPacket);
	loginPacket = new LoginUserPacket(*player->loginPacket);
	avatarPacket = new AvatarUserPacket(*player->avatarPacket);
	skillPacket = new SkillUserPacket(*player->skillPacket);
	itemPacket = new ItemUserPacket(*player->itemPacket);
}

LobbyPlayer::LobbyPlayer(const LobbyPlayer& player)
{
	Debug::error("DONT USE LobbyPlayer::LobbyPlayer(const LobbyPlayer&); USE THE POINTER STUFF");
}

LobbyPlayer::LobbyPlayer(LoginUserPacket* login, const sf::IpAddress& ip)
	: ip(ip)
{
	lockPacket = new LockUserPacket(false);
	teamPacket = new TeamUserPacket((char)0);
	itemPacket = new ItemUserPacket();
	avatarPacket = new AvatarUserPacket();
	skillPacket = new SkillUserPacket();
	loginPacket = new LoginUserPacket(*login);
}

LobbyPlayer::LobbyPlayer(LoginUserPacket* login)
	: ip(sf::IpAddress::getLocalAddress())
{
	lockPacket = new LockUserPacket(false);
	teamPacket = new TeamUserPacket((char)0);
	itemPacket = new ItemUserPacket();
	avatarPacket = new AvatarUserPacket();
	skillPacket = new SkillUserPacket();
	loginPacket = new LoginUserPacket(*login);
}

LobbyPlayer::LobbyPlayer(CompressBuffer* buffer)
	: ip(sf::IpAddress::getLocalAddress())
{
	lockPacket = static_cast<LockUserPacket*>(buffer->cutByCID(LOCK_USER_PACKET_CID));
	teamPacket = static_cast<TeamUserPacket*>(buffer->cutByCID(TEAM_USER_PACKET_CID));
	loginPacket = static_cast<LoginUserPacket*>(buffer->cutByCID(LOGIN_USER_PACKET_CID));
	avatarPacket = static_cast<AvatarUserPacket*>(buffer->cutByCID(AVATAR_USER_PACKET_CID));
	skillPacket = static_cast<SkillUserPacket*>(buffer->cutByCID(SKILL_USER_PACKET_CID));
	itemPacket = static_cast<ItemUserPacket*>(buffer->cutByCID(ITEM_USER_PACKET_CID));
}

sf::IpAddress LobbyPlayer::getIP() const
{
	return ip;
}

CID LobbyPlayer::getCID() const
{
	return LOBBY_PLAYER_CID;
}

LockUserPacket* LobbyPlayer::getLockUserPacket() const
{
	return lockPacket;
}

TeamUserPacket* LobbyPlayer::getTeamUserPacket() const
{
	return teamPacket;
}

LoginUserPacket* LobbyPlayer::getLoginUserPacket() const
{
	return loginPacket;
}

AvatarUserPacket* LobbyPlayer::getAvatarUserPacket() const
{
	return avatarPacket;
}

SkillUserPacket* LobbyPlayer::getSkillUserPacket() const
{
	return skillPacket;
}

ItemUserPacket* LobbyPlayer::getItemUserPacket() const
{
	return itemPacket;
}

void LobbyPlayer::applyLockUserPacket(LockUserPacket* packet)
{
	if (lockPacket != NULL)
	{
		deleteAndNULL(lockPacket);
	}
	lockPacket = new LockUserPacket(*packet);
}

void LobbyPlayer::applyTeamUserPacket(TeamUserPacket* packet)
{
	if (teamPacket != NULL)
	{
		deleteAndNULL(teamPacket);
	}
	teamPacket = new TeamUserPacket(*packet);
}

void LobbyPlayer::applyLoginUserPacket(LoginUserPacket* packet)
{
	if (loginPacket != NULL)
	{
		deleteAndNULL(loginPacket);
	}
	loginPacket = new LoginUserPacket(*packet);
}

void LobbyPlayer::applyAvatarUserPacket(AvatarUserPacket* packet)
{
	if (avatarPacket != NULL)
	{
		deleteAndNULL(avatarPacket);
	}
	avatarPacket = new AvatarUserPacket(*packet);
}

void LobbyPlayer::applySkillUserPacket(SkillUserPacket* packet)
{
	if (skillPacket != NULL)
	{
		deleteAndNULL(skillPacket);
	}
	skillPacket = new SkillUserPacket(*packet);
}

void LobbyPlayer::applyItemUserPacket(ItemUserPacket* packet)
{
	if (itemPacket != NULL)
	{
		deleteAndNULL(itemPacket);
	}
	itemPacket = new ItemUserPacket(*packet);
}

std::string LobbyPlayer::toString() const
{
	std::string s;
	s += getLockUserPacket()->toString();
	s += getTeamUserPacket()->toString();
	s += getLoginUserPacket()->toString();
	s += getAvatarUserPacket()->toString();
	s += getSkillUserPacket()->toString();
	s += getItemUserPacket()->toString();
	return s;
}
