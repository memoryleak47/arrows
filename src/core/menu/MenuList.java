package core.menu;

import java.util.LinkedList;
import java.awt.event.MouseListener;
import java.awt.event.KeyListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseEvent;
import java.awt.event.KeyEvent;

import core.menu.Menu;
import core.menu.menues.MainMenu;
import network.sendable.Event;
import network.sendable.events.*;
import core.Screen;

public class MenuList implements MouseMotionListener, MouseListener, KeyListener
{
	private LinkedList<Menu> menues;

	public MenuList()
	{
		menues = new LinkedList<Menu>();
		Screen.get().addMouseListener(this);
		Screen.get().addKeyListener(this);
		Screen.get().addMouseMotionListener(this);
		menues.add(new MainMenu());
	}

	public void tick()
	{
		getActiveMenu().tick();
	}

	public Menu getActiveMenu()
	{
		return menues.getLast();
	}
	
	public void render()
	{
		for (int i = getMenues().size()-1; i >= 0; i--)
		{
			menues.get(i).render();
			if (menues.get(i).isFullscreen())
			{
				break;
			}
		}
	}

	void onEvent(Event event)
	{
		menues.getLast().onEvent(event);
	}
	
	@Override public void mouseClicked(MouseEvent event) {}
	@Override public void mouseEntered(MouseEvent event) {}
	@Override public void mouseExited(MouseEvent event) {}
	@Override public void mouseDragged(MouseEvent event) {}

	@Override public void mousePressed(MouseEvent event)
	{
		onEvent(new MouseButtonPress(event));
	}

	@Override public void mouseReleased(MouseEvent event)
	{
		onEvent(new MouseButtonRelease(event));
	}

	@Override public void mouseMoved(MouseEvent event)
	{
		onEvent(new MouseMove(event));
	}

	@Override public void keyPressed(KeyEvent event)
	{
		onEvent(new KeyPress(event));
	}

	@Override public void keyReleased(KeyEvent event)
	{
		onEvent(new KeyRelease(event));
	}

	@Override public void keyTyped(KeyEvent event) {}

	public LinkedList<Menu> getMenues() { return menues; }
}
