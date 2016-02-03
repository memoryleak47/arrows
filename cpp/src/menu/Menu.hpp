#ifndef __MENU_CLASS__
#define __MENU_CLASS__

#include <string>
#include <SFML/Window.hpp>

#include "ComponentContainer.hpp"

class Menu : public ComponentContainer
{
	public:
		Menu(const PixelRect& rect); // windowed menu
		Menu(); // fullscreen window
		virtual bool isFullscreen();
		virtual void tick();
		void render() const override;
		void onEvent(const sf::Event&);
		virtual bool isNetworkingMenu() const;
	protected:
		static void popup(const std::string&);
	private:
		MenuComponent* getFocusedComponent();
		MenuComponent* focusedComponent;
};

#endif