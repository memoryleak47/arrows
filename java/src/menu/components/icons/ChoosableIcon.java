/*
	Überklasse aller Icons die im PlayerPanel platziert sind

	AvatarIcon, SkillIcon, ItemIcon
*/

package menu.components.icons;

import java.awt.Color;

import core.Screen;
import menu.components.Icon;
import menu.components.PlayerPanel;
import menu.ComponentContainer;
import menu.menues.LobbyMenu;
import misc.math.pixel.PixelRect;
import misc.Debug;
import player.LobbyPlayer;

public abstract class ChoosableIcon extends Icon
{
	public ChoosableIcon(ComponentContainer parent, PixelRect rect)
	{
		super(parent, rect);
	}

	@Override public void render()
	{
		super.render();
		if (isChoosable())
		{
			// Hervorhebung. Zeichnet weißes durchsichtiges Viereck auf das Icon
			Screen.g().setColor(new Color(255, 255, 255, 125));
			Screen.g().fillRect(getOffset().getX(), getOffset().getY(), getWidth(), getHeight());
		}
	}

	// returnt, ob dieses Icon angeklickt werden kann, um den Inhalt zu ändern
	public boolean isChoosable()
	{
		if (getParentMenu() instanceof LobbyMenu)
		{

			boolean chosen = getLobbyMenu().getPhase() == getChoosePhase()
				&& getLobbyMenu().getLocalPlayer() == getPlayer()
				&& !getPlayer().isLocked();
			return chosen;
		}
		return false;
	}

	// getter
	protected LobbyMenu getLobbyMenu() { return ((LobbyMenu) getParentMenu()); }
	protected LobbyPlayer getPlayer() { return ((PlayerPanel) getParent()).getPlayer(); }

	// Setter

	// Abstrakte Funktionen
	// returnt die Phase in der das Icon beim LocalPlayer ausgewählt werden kann
	public abstract int getChoosePhase();
}
