#ifndef __MENULIST_CLASS__
#define __MENULIST_CLASS__

#define IS_DEBUG_MODE true

#include <vector>
#include <SFML/Window.hpp>

class Menu;

class MenuList
{
	public:
		MenuList();
		virtual ~MenuList();
		void onEvent(const sf::Event &event);
		void tick();
		void render();
		void addMenu(Menu*);
		void back(); // removes menu
	private:
		std::vector<Menu*> menues;
		std::vector<Menu*> getMenues(); // TODO correct data type?
		Menu* getTopmostMenu();
		int getTopmostFullscreenMenuIndex();
};

#include "Menu.hpp"

#endif
