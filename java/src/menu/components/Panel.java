package menu.components;

import java.awt.Color;

import core.Screen;
import menu.ComponentContainer;
import menu.MenuComponent;
import menu.Menu;
import misc.math.pixel.PixelRect;
import misc.math.pixel.PixelSize;

public class Panel extends ComponentContainer
{
	private static final PixelSize padding = new PixelSize(20, 20); // über "padding" wird der Abstand innerhalb des KomponentenContainers zu den Komponenten gespeichert. Wird in calcSize() benötigt

	public Panel(ComponentContainer parent, PixelRect rect)
	{
		super(parent, rect);
	}

	@Override public void render()
	{
		super.render(); // rendere alle MenuComponents
		Screen.g().setColor(Color.BLUE);
		Screen.g().drawRect(getOffset().getX(), getOffset().getY(), getWidth()-1, getHeight()-1); // zeichne blauen rand
	}

	// ändert die Size des Panels so, dass zwischen der Komponente links unten noch padding Platz ist
	public void calcSize()
	{
		int right = 0;
		int bot = 0;

		// sucht die width/height indem alle Komponenten durchlaufen werden und die am weitesten rechts und unten gespeichert werden
		for (MenuComponent component : getComponents())
		{
			right = Math.max(right, component.getRight() + padding.getX());
			bot = Math.max(bot, component.getBot() + padding.getY());
		}

		if (right != this.getWidth())
		{
			this.setWidth(right);
		}

		if (bot != this.getHeight())
		{
			this.setHeight(bot);
		}
	}
}
