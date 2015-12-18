/*
	Alle Spieler des Servers sind von diesem Typ. Kommt nicht im Client vor.
*/

package network.game.player;

import java.net.InetAddress;
import java.util.LinkedList;

import entity.Entity;
import entity.part.EffectEntityPart;
import entity.part.LivingEntityPart;
import entity.part.PhysicsEntityPart;
import entity.part.parts.living.PlayerLivingEntityPart;
import entity.part.parts.physics.DynamicPhysicsEntityPart;
import entity.part.property.properties.living.MortalLivingEntityPartProperty;
import graphics.ImageID;
import misc.Debug;
import misc.game.effect.Effect;
import misc.game.kill.KDCounter;
import misc.game.PlayerStats;
import misc.game.Team;
import misc.math.Position;
import network.lobby.LobbyPlayer;
import network.game.player.LocalClientGamePlayerFrameUpdate;
import network.game.player.ClientGamePlayerFrameUpdate;
import playerproperty.avatar.Avatar;
import playerproperty.skill.Skill;
import playerproperty.item.Item;

public class ServerGamePlayer extends Entity implements GamePlayer
{
	private InetAddress ip;

	private String name;
	private int rank;
	private Team team;

	// PlayerProperties
	private Avatar avatar;
	private Skill[] skills;
	private Item[] items;

	private PlayerStats playerStats;
	private short[] charges;

	private KDCounter kdCounter = new KDCounter();

	public ServerGamePlayer(LobbyPlayer lobbyPlayer, Position position)
	{
		this.ip = lobbyPlayer.getIP();
		this.name = lobbyPlayer.getName();
		this.rank = lobbyPlayer.getRank();
		this.team = lobbyPlayer.getTeam();
		this.skills = lobbyPlayer.getSkills();
		this.items = lobbyPlayer.getItems();
		this.avatar = lobbyPlayer.getAvatar();
		((DynamicPhysicsEntityPart) getPhysicsEntityPart()).init(calcMass());
	}

	public LocalClientGamePlayerFrameUpdate toLocalClientGamePlayerFrameUpdate()
	{
		return new LocalClientGamePlayerFrameUpdate(Effect.toMinimizedEffects(getEffects()) , getPlayerStats(), getCharges());
	}

	public ClientGamePlayerFrameUpdate toClientGamePlayerFrameUpdate()
	{
		return new ClientGamePlayerFrameUpdate(getHealth(), getPosition(), getImageID());
	}

	// Entity-creater
	@Override public PhysicsEntityPart createPhysicsEntityPart()
	{
		return new DynamicPhysicsEntityPart(this);
	}

	@Override public LivingEntityPart createLivingEntityPart()
	{
		return new PlayerLivingEntityPart(this);
	}

	@Override public EffectEntityPart createEffectEntityPart()
	{
		Debug.warn("ServerGamePlayer.createEffectEntityPart(): TODO");
		return null;
	}

	private int calcMass()
	{
		int mass = getAvatar().getMassStat();
		for (int i = 0; i < getItems().length; i++)
		{
			mass += getItems()[i].getMassStat();
		}
		return mass;
	}

	// getter
	public InetAddress getIP() { return ip; }
	@Override public String getName() { return name; }
	public int getRank() { return rank; }

	public short[] getCharges() { return charges; }
	@Override public LinkedList<Integer> getEffectIDs() { return Effect.toEffectIDs(getEffects()); }
	public PlayerStats getPlayerStats() { return playerStats; }

	public Avatar getAvatar() { return avatar; }
	public Skill[] getSkills() { return skills; }
	public Item[] getItems() { return items; }

	public KDCounter getKDCounter() { return kdCounter; }

	// may be done by Entity
	public LinkedList<Effect> getEffects() { return getEffectEntityPart().getEffects(); }
	@Override public Team getTeam() { return team; }
	@Override public Position getPosition() { return getPhysicsEntityPart().getPosition(); }
	@Override public int getHealth() { return ((MortalLivingEntityPartProperty)getLivingEntityPart()).getHealth(); }
	@Override public ImageID getImageID() { Debug.warn("ServerGamePlayer.getImageID(): TODO"); return null; }

	/*
		getHealth, getPosition, getImageID, getEffects, sind schon von Entity definiert und müssen nicht nochmal geschrieben werden
	*/
}
