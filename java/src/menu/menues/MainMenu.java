package menu.menues;

import core.Main;
import menu.Menu;
import menu.MenuComponent;
import menu.components.*;
import misc.Debug;
import misc.math.pixel.*;

public class MainMenu extends Menu
{
	public MainMenu()
	{
		getComponents().add(new Label(this, new PixelRect(400, 10, 200, 40), "Main Menu"));
		getComponents().add(new EditField(this, new PixelRect(200, 200, 100, 100), "text"));
		getComponents().add(new Button(this, new PixelRect(300, 100, 100, 30), "Create Server")
		{
			@Override public void onClick(int mouseButton)
			{
				Main.getMenues().add(new CreateServerMenu());
			}
		});
		getComponents().add(new Button(this, new PixelRect(300, 150, 100, 30), "Join Server")
		{
			@Override public void onClick(int mouseButton)
			{
				Main.getMenues().add(new JoinServerMenu());
			}
		});
		getComponents().add(new Button(this, new PixelRect(140, 500, 100, 30), "Logout")
		{
			@Override public void onClick(int mouseButton)
			{
				Main.getMenues().remove(Main.getMenues().getLast());
			}
		});
		getComponents().add(new QuitButton(this, new PixelRect(20, 500, 100, 30)));
	}

}
