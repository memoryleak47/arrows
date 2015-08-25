package network.game.packets.events;

import java.awt.event.KeyEvent;

import network.game.packets.EventPacket;

public final class KeyPressEventPacket extends EventPacket
{
	private char key;

	public KeyPressEventPacket(KeyEvent keyEvent)
	{
		key = keyEvent.getKeyChar();
	}

	public char getKeyChar() { return key; }
}