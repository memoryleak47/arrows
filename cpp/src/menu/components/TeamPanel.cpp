#include "TeamPanel.hpp"

#include "PlayerPanel.hpp"
#include <misc/Debug.hpp>
#include <menu/components/Button.hpp>
#include <menu/components/TeamListPanel.hpp>
#include <menu/menues/LobbyMenu.hpp>
#include <team/Team.hpp>
#include <player/LobbyPlayer.hpp>
#include <network/packets/TeamPacket.hpp>

TeamPanel::TeamPanel(LobbyMenu* m, TeamListPanel* c, const PixelRect& r, Team* team)
	: Panel(c, r), lobby(m), teamButton(nullptr), team(team)
{}

void TeamPanel::update(const std::vector<LobbyPlayer*>& players)
{
	bool buttonWasEnabled = (teamButton == nullptr || teamButton->isEnabled());

	clearComponents();
	class TeamButton : public Button
	{
		public:
			TeamButton(TeamPanel* c, const PixelRect& r, const std::string& h) : Button(c, r, h), panel(c) {}
			virtual void onPress() override
			{
				panel->getLobbyMenu()->teamPressed(panel->getTeam()); // Übergabe an LobbyMenu, dass wir Team wechseln
			}
		private:
			TeamPanel* panel;
	};
	addComponent(teamButton = new TeamButton(this, PixelRect(20, 20, 100, 30), "Team " + team->getName()));

	teamButton->setEnabled(buttonWasEnabled);

	int c = 0;
	for (unsigned int i = 0; i < players.size(); i++)
	{
		if (players[i] == nullptr)
		{
			Debug::error("TeamPanel::update(): player is nullptr");
			return;
		}

		if (players[i]->getTeamPacket()->getTeam() == team)
		{
			addComponent(new PlayerPanel(players[i], getLobbyMenu(), this, PixelRect(getRelativeRect().getPosition().x + 5 + c*65, 55, 60, 60)));
			c++;
		}
	}
}

LobbyMenu* TeamPanel::getLobbyMenu() const
{
	return lobby;
}

Team* TeamPanel::getTeam() const
{
	return team;
}

void TeamPanel::disableTeamButton()
{
	teamButton->setEnabled(false);
}
