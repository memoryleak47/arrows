package network.lobby.packets.user;

import misc.game.Team;
import network.lobby.packets.UserPacket;

public class TeamUserPacket extends UserPacket
{
	private int teamID;

	public TeamUserPacket(Team team)
	{
		teamID = team.getID();
	}

	public void assign(TeamUserPacket teamPacket)
	{
		// TODO fehlerabfragen
		teamID = teamPacket.teamID;
	}


	public TeamUserPacket(TeamUserPacket packet)
	{
		teamID = packet.teamID;
	}

	public Team getTeam()
	{
		return Team.getByID(teamID);
	}
}
