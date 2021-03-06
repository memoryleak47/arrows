/*
	Alle externen Player des Clients sind von der Klasse ClientGamePlayer.
	Diese werden durch ClientGamePlayerFrameUpdate geupdated (apply-Funktion).
*/

package player;

import java.util.LinkedList;

import core.Screen;
import effect.Effect;
import entity.Entity;
import entity.MinimizedEntity;
import graphics.ImageID;
import graphics.ImageFile;
import misc.Debug;
import player.property.Team;
import damage.KDCounter;
import misc.compress.Compressor;
import misc.math.Camera;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;
import misc.math.pixel.PixelPosition;
import player.LobbyPlayer;
import player.property.avatar.Avatar;
import player.property.skill.Skill;
import player.property.item.Item;

public class ClientGamePlayer extends MinimizedEntity implements GamePlayer
{
	private String name;
	private int rank;
	private Team team;

	// Player Properties
	private Avatar avatar;
	private Skill[] skills;
	private Item[] items;

	private KDCounter kdCounter = new KDCounter();
	private float health;
	private float maxHealth;

	public ClientGamePlayer(LobbyPlayer player)
	{
		super(new GamePosition(), ImageFile.VOID_ICON.getImageID(), new boolean[Effect.EFFECTS_SIZE]);
		name = player.getName();
		rank = player.getRank();
		avatar = player.getAvatar();
		team = player.getTeam();
		skills = player.getSkills();
		items = player.getItems();
	}

	public void apply(ClientGamePlayerFrameUpdate update)
	{
		maxHealth = update.getMaxHealth();
		health = update.getHealth();
		setPosition(update.getPosition());
		setImageID(update.getImageID());
		setEffectIDs(update.getEffectIDs());
	}

	@Override public void render()
	{
		super.render();
		Screen.g().setColor(team.getColor());
		GamePosition gamePos = new GamePosition(getPosition());
		gamePos = gamePos.plusY(getSize().getY()/-2);
		PixelPosition pos = Camera.get().gamePositionToPixelPosition(gamePos);
		int length = (int) ((health / maxHealth)*50.f);
		Screen.g().fillRect((int) (pos.getX()-(float)length/2), pos.getY() - 20, length, 5);
		renderEffects();
	}

	// getter
	@Override public String getName() { return name; }
	public int getRank() { return rank; }
	@Override public Team getTeam() { return team; }

	public Avatar getAvatar() { return avatar; }
	@Override public Skill[] getSkills() { return skills; }
	public Item[] getItems() { return items; }

	public KDCounter getKDCounter() { return kdCounter; }

	@Override public float getHealth() { return health; }

	@Override public byte getCID()
	{
		Debug.warn("ClientGamePlayer.getCID(): should never be called, returning -1");
		return -1;
	}

	@Override public byte[] compress()
	{
		Debug.warn("ClientGamePlayer.compress(): should never be called, returning null");
		return null;
	}
}
