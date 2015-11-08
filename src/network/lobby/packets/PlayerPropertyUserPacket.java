/*
	Avatar, Skill, Item
*/

package network.lobby.packets;

import playerproperty.PlayerProperty;

public interface PlayerPropertyUserPacket
{
	public PlayerProperty[] getPlayerProperty();
	public void setIDs(byte[] ids);
}
