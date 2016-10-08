#include "LobbyMenu.hpp"

#include <misc/compress/Compressable.hpp>
#include <menu/components/Label.hpp>
#include <core/Screen.hpp>
#include <core/Main.hpp>
#include <misc/Converter.hpp>
#include <misc/Debug.hpp>

LobbyMenu::LobbyMenu()
{
	tileMap = new LobbyTileMap();

	phase = TEAM_PHASE;
	
	addComponent(new Label(this, PixelRect(300, 10, 150, 20), "Lobby"));

	class LockButton : public Button
	{
		public:
			LockButton(LobbyMenu* c, const PixelRect& r, const std::string& s) : Button(c, r, s) {}
			virtual void onPress() override
			{
				((LobbyMenu*)getParent())->lockPressed();
			}
	};
	addComponent(lockButton = new LockButton(this, PixelRect(Screen::getSize().x - 250, 600, 200, 60), "Lock"));

	addComponent(miniMap = new LobbyMiniMap(this, PixelRect(Screen::getSize().x - 250, 100, 200, 140)));

	class DisconnectButton : public Button
	{
		public:
			DisconnectButton(LobbyMenu* c, const PixelRect& r, const std::string& s) : Button(c, r, s) {}
			virtual void onPress() override
			{
				((LobbyMenu*)getParent())->disconnectPressed();
			}
	};
	addComponent(new DisconnectButton(this, PixelRect(20, 500, 20, 20), "Disconnect"));
	addComponent(teamListPanel = new TeamListPanel(this, PixelRect(100, 100, 600, 600)));
}

LobbyMenu::~LobbyMenu()
{
	deleteAndNULL(tileMap);
	deleteAndClearVector(players);
}

std::vector<LobbyPlayer*> LobbyMenu::getPlayers() const
{
	return players;
}

LobbyTileMap* LobbyMenu::getLobbyTileMap() const
{
	return tileMap;
}

bool LobbyMenu::areAllClientsLocked() const
{
	for (unsigned int i = 1; i < getPlayers().size(); i++)
	{
		if (!getPlayer(i)->getLockUserPacket()->isLocked())
			return false;
	}
	return true;
}

int LobbyMenu::getPhase() const
{
	return phase;
}

void LobbyMenu::tick()
{
	Menu::tick();
	handleAllPackets();
	updateLockButton();
}

int LobbyMenu::ipToID(sf::IpAddress* ip, const std::vector<LobbyPlayer*>& players) const
{
	for (unsigned int i = 0; i < players.size(); i++)
	{
		if ((*players[i]->getIP()) == (*ip))
		{
			return i;
		}
	}
	Debug::warn("LobbyMenu::ipToID(): no Player with this ip: " + ip->toString());
	return -1;
}

void LobbyMenu::updatePlayerIcons() const
{
	teamListPanel->update();
}

LobbyPlayer* LobbyMenu::getPlayer(int id) const
{
	if (id < 0 || id >= (int)getPlayers().size()) Debug::warn("LobbyMenu::getPlayer(): id out of range: " + Converter::intToString(id) + "; size of Players(): " + Converter::intToString(getPlayers().size()));
	return players[id];
}

void LobbyMenu::addPlayer(LobbyPlayer* p)
{
	players.push_back(p);
}

void LobbyMenu::updateMap(const std::vector<std::vector<int>>& ints)
{
	miniMap->updateMap(ints);
	tileMap->updateMap(ints);
}

void LobbyMenu::unlockAll()
{
	LockUserPacket* packet = new LockUserPacket(false);
	for (unsigned int i = 0; i < getPlayers().size(); i++)
	{
		getPlayers()[i]->applyLockUserPacket(packet);
	}
	delete packet;
}

void LobbyMenu::nextPhase()
{
	phase++;
	if (phase == AVATAR_PHASE)
	{
		teamListPanel->disableTeamButtons();
	}
	else if (phase == GAME_PHASE)
	{
		createGameInterface();
		resetLobby();
	}
	unlockAll();
}

void LobbyMenu::removePlayer(int id)
{
	deleteAndNULL(players[id]);
	players.erase(players.begin() + id);
}

void LobbyMenu::clearPlayers()
{
	deleteAndClearVector(players);
}

void LobbyMenu::resetLobby()
{
	unlockAll();
	deleteAndNULL(tileMap);
	// TODO more!
	Debug::warn("LobbyMenu::resetLobby(): TODO");
}
