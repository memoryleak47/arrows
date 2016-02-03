#ifndef __TEXTUREMANAGER_CLASS__
#define __TEXTUREMANAGER_CLASS__

#include <SFML/Graphics.hpp>

typedef int TextureID;

class TextureManager
{
	public:
		static void init();
		static void uninit();
		static sf::Texture* getTexture(const TextureID&);
	private:
		static void addImage(int*, const std::string&);
		static sf::Texture** textures;
		static int idCounter;
};

#endif