#include "Screen.h"

sf::RenderWindow* Screen::window;

void Screen::init()
{
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Arrows");
}

void Screen::uninit()
{
	window->close();
	delete window;
}

void Screen::tick()
{
	static sf::Event event;
	window->pollEvent(event);
	if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		Main::exit();
	}
	else
	{
		Main::getMenuList()->onEvent(event);
	}
}

void Screen::display()
{
	window->display();
	window->clear();
}

void Screen::drawRect(const PixelRect& rect, const sf::Color& color)
{
	
}

void Screen::drawImageID(const ImageID& id, const PixelRect& rect)
{
	
}

void Screen::drawText(const std::string& s, const PixelRect& rect, const sf::Color& color)
{
	
}
