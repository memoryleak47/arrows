#ifndef __LOBBYMENU_CLASS__
#define __LOBBYMENU_CLASS__

#define TEAM_PHASE 0
#define AVATAR_PHASE 1
#define SKILL_PHASE 2
#define ITEM_PHASE 3
#define GAME_PHASE 4

#include <SFML/Network.hpp>
#include <vector>

#include "../NetworkingMenu.hpp"

class Button;
class Team;
class LobbyTileMap;
class LobbyMiniMap;
class LobbyPlayer;
class TeamListPanel;
class LockUserPacket;
class DisconnectUserPacket;
class TeamUserPacket;
class LoginUserPacket;
class AvatarUserPacket;
class SkillUserPacket;
class ItemUserPacket;
class MapPacket;
class UserPacketWithID;
class LobbyPlayersPacket;

class LobbyMenu : public NetworkingMenu
{
	public:
		LobbyMenu();
		int getPhase() const;
		std::vector<LobbyPlayer*> getPlayers() const;
		virtual void lockPressed() = 0;
		virtual void disconnectPressed() = 0;
		virtual void teamPressed(Team*) = 0;
		virtual LobbyPlayer* getLocalPlayer() const = 0;
	protected:
		int ipToID(const sf::IpAddress&, const std::vector<LobbyPlayer*>&) const;
		void handlePacketByID(Packet*, int);
		void updatePlayerIcons() const;
		// handle Packets
		virtual void handleLockUserPacket(LockUserPacket*, int);
		virtual void handleDisconnectUserPacket(DisconnectUserPacket*, int);
		virtual void handleTeamUserPacket(TeamUserPacket*, int);
		virtual void handleLoginUserPacket(LoginUserPacket*, int);
		virtual void handleAvatarUserPacket(AvatarUserPacket*, int);
		virtual void handleSkillUserPacket(SkillUserPacket*, int);
		virtual void handleItemUserPacket(ItemUserPacket*, int);
		virtual void handleMapPacket(MapPacket*, int);
		virtual void handleUserPacketWithID(UserPacketWithID*, int);
		virtual void handleLobbyPlayersPacket(LobbyPlayersPacket*, int);

		Button* lockButton; // Verweiß auf den NextStep/LockIn Button
	private:
		int phase;
		LobbyTileMap* lobbyTileMap;
		LobbyMiniMap* miniMap;
		std::vector<LobbyPlayer*> players; // Bluemi: protected -> private; added setter
		TeamListPanel* teamListPanel; // Nicht zwingend nötig, nur einfacherer Zugriff, da nicht über index
};

#include "../components/Button.hpp"
#include "../../player/property/Team.hpp"
#include "../../tile/map/LobbyTileMap.hpp"
#include "../components/LobbyMiniMap.hpp"
#include "../../player/LobbyPlayer.hpp"
#include "../components/TeamListPanel.hpp"
#include "../../network/packets/LockUserPacket.hpp"
#include "../../network/packets/DisconnectUserPacket.hpp"
#include "../../network/packets/TeamUserPacket.hpp"
#include "../../network/packets/LoginUserPacket.hpp"
#include "../../network/packets/AvatarUserPacket.hpp"
#include "../../network/packets/SkillUserPacket.hpp"
#include "../../network/packets/ItemUserPacket.hpp"
#include "../../network/packets/MapPacket.hpp"
#include "../../network/packets/UserPacketWithID.hpp"
#include "../../network/packets/LobbyPlayersPacket.hpp"

#endif