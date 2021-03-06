package network.game.packets;

import java.util.LinkedList;

import player.ClientGamePlayerFrameUpdate;
import player.LocalClientGamePlayerFrameUpdate;
import bullet.MinimizedBullet;
import misc.compress.*;
import network.Packet;
import network.game.packets.EventUpdatePacket;

public class GameFrameUpdatePacket extends Packet
{
	private LinkedList<ClientGamePlayerFrameUpdate> players;
	private LinkedList<MinimizedBullet> bullets;
	private LinkedList<EventUpdatePacket> eventUpdatePackets;
	private LocalClientGamePlayerFrameUpdate localClientGamePlayerFrameUpdate;

	public GameFrameUpdatePacket(LinkedList<ClientGamePlayerFrameUpdate> players, LinkedList<MinimizedBullet> bullets, LinkedList<EventUpdatePacket> eventUpdatePackets, LocalClientGamePlayerFrameUpdate localClientGamePlayerFrameUpdate)
	{
		this.players = players;
		this.bullets = bullets;
		this.eventUpdatePackets = eventUpdatePackets;
		this.localClientGamePlayerFrameUpdate = localClientGamePlayerFrameUpdate;
	}

	@SuppressWarnings("unchecked")
	public GameFrameUpdatePacket(CompressBuffer buffer)
	{
		players = buffer.cutListByCID(Compressor.CLIENT_GAME_PLAYER_FRAME_UPDATE_CID);
		bullets = buffer.cutListByCID(Compressor.MINIMIZED_BULLET_CID);
		localClientGamePlayerFrameUpdate = (LocalClientGamePlayerFrameUpdate) buffer.cutByCID(Compressor.LOCAL_CLIENT_GAME_PLAYER_FRAME_UPDATE_CID);
	}

	@Override public byte getCID() { return Compressor.GAME_FRAME_UPDATE_PACKET_CID; }
	@Override public byte[] compress()
	{
		return Compressor.concat( new byte[][]{
			Compressor.compressList(getPlayerUpdates()),
			Compressor.compressList(getBullets()),
			//Compressor.compressList(getEventUpdatePackets()),
			getLocalClientGamePlayerFrameUpdate().compress()
		});
	}

	// getter

	public LinkedList<ClientGamePlayerFrameUpdate> getPlayerUpdates() { return players; }
	public LinkedList<MinimizedBullet> getBullets() { return bullets; }
	public LinkedList<EventUpdatePacket> getEventUpdatePackets() { return eventUpdatePackets; }
	public LocalClientGamePlayerFrameUpdate getLocalClientGamePlayerFrameUpdate() { return localClientGamePlayerFrameUpdate; }
}
