/*
 * PlayerPanel ist 60x60 Pixel groß.
 * AvatarIcon ist 45x45 Pixel groß.
 * {Item,Skill}Icons sind 15x15 Pixel groß.
 * 0; 15; 30; 45; 60
*/

package menu.components;

import java.awt.Color;

import core.Screen;
import menu.ComponentContainer;
import menu.components.icons.AvatarIcon;
import menu.components.icons.SkillIcon;
import menu.components.icons.ItemIcon;
import misc.Debug;
import misc.math.Rect;
import network.lobby.LobbyPlayer;

public class PlayerPanel extends ComponentContainer
{
	public static final int SKILL_ICON_SIZE = 15, ITEM_ICON_SIZE = 15, AVATAR_ICON_SIZE = 45;

	private LobbyPlayer player;

	public PlayerPanel(ComponentContainer parent, Rect rect, LobbyPlayer player)
	{
		super(parent, rect);
		this.player = player;

		// AvatarIcon
		getComponents().add(new AvatarIcon(this, new Rect(0,0,AVATAR_ICON_SIZE,AVATAR_ICON_SIZE), this.player.getAvatar()));

		// SkillIcons
		getComponents().add(new SkillIcon(this, new Rect(0,45,SKILL_ICON_SIZE,SKILL_ICON_SIZE), this.player.getSkills()[0]));
		getComponents().add(new SkillIcon(this, new Rect(15,45,SKILL_ICON_SIZE,SKILL_ICON_SIZE), this.player.getSkills()[1]));
		getComponents().add(new SkillIcon(this, new Rect(30,45,SKILL_ICON_SIZE,SKILL_ICON_SIZE), this.player.getSkills()[2]));
		getComponents().add(new SkillIcon(this, new Rect(45,45,SKILL_ICON_SIZE,SKILL_ICON_SIZE), this.player.getSkills()[3]));

		// ItemIcons
		getComponents().add(new ItemIcon(this, new Rect(45,0,ITEM_ICON_SIZE,ITEM_ICON_SIZE), this.player.getItems()[0]));
		getComponents().add(new ItemIcon(this, new Rect(45,15,ITEM_ICON_SIZE,ITEM_ICON_SIZE), this.player.getItems()[1]));
		getComponents().add(new ItemIcon(this, new Rect(45,30,ITEM_ICON_SIZE,ITEM_ICON_SIZE), this.player.getItems()[2]));
	}

	@Override public void render()
	{
		super.render(); // zeichne alle MenuComponents
		if (player != null && player.isLocked())
		{
			Screen.g().setColor(Color.YELLOW);
			Screen.g().drawRect(getOffset().getX()-2, getOffset().getY()-2, getWidth()+4, getHeight()+4);
		}
	}

	public LobbyPlayer getPlayer() { return player; }
}