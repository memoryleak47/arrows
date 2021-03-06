package menu.components.icons.choosable;

import core.Main;
import menu.components.icons.ChoosableIcon;
import menu.ComponentContainer;
import menu.menues.LobbyMenu;
import menu.menues.ChoosePlayerPropertyMenu;
import player.property.skill.Skill;
import graphics.ImageID;
import graphics.ImageFile;
import misc.Debug;
import misc.math.pixel.PixelRect;
import player.LobbyPlayer;

public class SkillIcon extends ChoosableIcon
{
	private LobbyPlayer player;
	private int number;

	public SkillIcon(ComponentContainer parent, PixelRect rect, LobbyPlayer player, int number)
	{
		super(parent, rect);
		this.player = player;
		this.number = number;
	}

	@Override public void onClick(int mouseButton)
	{
		if (isChoosable())
		{
			LobbyPlayer player = getLobbyMenu().getLocalPlayer();
			Main.getMenues().add(new ChoosePlayerPropertyMenu(getLobbyMenu(), player.getSkillPacket(), Skill.getAllSkillsByAvatarID(player.getAvatar().getID())));
		}
	}

	// getter
	@Override public int getChoosePhase() { return LobbyMenu.SKILL_PHASE; }
	@Override public ImageID getImageID()
	{
		if ((player.getSkillPacket() == null) 
				|| (player.getSkillPacket().getSkills()[number] == null) 
				|| (player.getSkillPacket().getSkills()[number].getIconImageID() == null))
		{
			return ImageFile.VOID_ICON.getImageID();
		}
		return player.getSkillPacket().getSkills()[number].getIconImageID();
	}
	public Skill getSkill() { return player.getSkillPacket().getSkills()[number]; }
}
