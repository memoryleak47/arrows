package core.menu.menues;

import core.menu.Menu;
import network.sendable.Event;

public class GameInterface extends Menu
// gives Event to NetworkDevice.onEvent(event)
{
	// TODO much
	@Override public boolean isFullscreen() { return true; }
}
