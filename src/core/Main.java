package core;

import java.util.Timer;
import java.util.TimerTask;
import java.util.LinkedList;
import java.util.HashMap;

import core.menu.Menu;
import core.menu.MenuList;
import misc.Account;
import misc.Debug;
import static misc.Serializer.*;
import network.NetworkDevice;

public class Main
{
	public static final int FRAME_INTERVAL = 40; // intervall in dem tick() und render() ausgeführt werden

	private static MenuList menuList;
	private static NetworkDevice networkDevice;
	private static Account account;

	public static void main(String args[])
	{
		new Main().run(); // neue Main-instanz erstellen und deren run funktion ausführen
	}

	private void run()
	{
		init(); // initalisieren

		new Timer().scheduleAtFixedRate(new TimerTask() // wiederhole alle <FRAME_INTERVAL> ms
		{
			@Override
			public void run()
			{
				tick(); // tick
				render(); // render
			}
		}, FRAME_INTERVAL, FRAME_INTERVAL);

		while (true) // wiederhole für immer
		{
			networkDevice.receive(); // erhalte packets und gebe sie an das NetworkingMenu von networkDevice weiter
		}
	}

	private void init()
	{
		Debug.init();
		Screen.init(); // init Screen
		menuList = new MenuList(); // init menuList
		networkDevice = new NetworkDevice(); // init networkDevice
	}

	public static void quit()
	{
		if (account != null) // falls du eingeloggt bist
		{
			Account.updateAccount(account); // speichere die änderungen an deinem account
		}
		Debug.quit("closed properly"); // beende das programm
	}

	private void tick()
	{
		menuList.tick(); // ticke menuList
	}

	private void render()
	{
		Screen.render(); // rendere die menuList auf den 'Screen
	}

	// needed for LoginMenu
	public static void setAccount(Account newAccount) { account = newAccount; }

	// gebraucht zum erstellen eines LoginUserPackets für diesen spieler 
	public static String getName() { return getAccount().getName(); }
	public static int getRank() { return getAccount().getRank(); }

	// gebraucht für das darüber ^^
	public static Account getAccount() { return account; }

	// gebrauch in MenuComponent to add or remove menues
	public static LinkedList<Menu> getMenues() { return getMenuList().getMenues(); }

	// gebraucht in Screen.render()
	public static MenuList getMenuList() { return menuList; }

	// gebraucht in NetworkingMenu zum setzen der networkDevice.menu
	public static NetworkDevice getNetworkDevice() { return networkDevice; }
}
