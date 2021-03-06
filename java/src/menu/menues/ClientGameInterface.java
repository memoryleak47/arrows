package menu.menues;

import java.net.InetAddress;
import java.util.LinkedList;

import core.Main;
import game.ClientGame;
import network.game.packets.GameFrameUpdatePacket;
import tile.map.LobbyTileMap;
import misc.Debug;
import network.Packet;
import menu.event.Event;
import player.LobbyPlayer;

public class ClientGameInterface extends GameInterface
{
	private InetAddress serverIP;

	public ClientGameInterface(LobbyTileMap map, LinkedList<LobbyPlayer> lobbyPlayers, int localPlayerID, InetAddress serverIP)
	{
		super(new ClientGame(map, lobbyPlayers, localPlayerID));
		Debug.warnIf(serverIP == null, "ClientGameInterface.<init>(): serverIP is null");
		this.serverIP = serverIP;
	}

	@Override public void tick()
	{
		super.tick();
		send(getPlayerControlsUpdatePacket(), serverIP);
	}

	@Override protected float[] getLocalPlayerCharges()
	{
		return getGame().getLocalPlayerCharges();
	}

	private ClientGame getGame() { return (ClientGame) getUncastedGame(); }

	@Override public void handlePacket(Packet packet, InetAddress ip)
	{
		if (packet instanceof GameFrameUpdatePacket)
		{
			getGame().apply((GameFrameUpdatePacket) packet);
		}
		else
		{
			Debug.warn("ClientGameInterface.handlePacket(): Unknown Packet: " + packet.toString());
		}
	}

	@Override public void render()
	{
		super.render();
	}

	@Override public void onEvent(Event packet)
	{
		super.onEvent(packet);
		// Main.getNetworkDevice().send(packet, serverIP);
	}
}
