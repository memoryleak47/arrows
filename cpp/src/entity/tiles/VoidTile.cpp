#include "VoidTile.hpp"

VoidTile::VoidTile(const GameVector& pos)
	: Tile(new RectBody(pos))
{}

sf::Texture* VoidTile::getTexture() const
{
	return GraphicsManager::getTexture(VOIDTILE_GID);
}
