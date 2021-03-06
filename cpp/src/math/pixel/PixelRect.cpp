#include "PixelRect.hpp"

PixelRect::PixelRect(int x, int y, int w, int h) : position(x, y), size(w, h)
{}

PixelRect::PixelRect(const PixelRect& rect) : position(rect.getPosition()), size(rect.getSize())
{}

PixelRect::PixelRect(const PixelVector& position, const PixelVector& size) : position(position), size(size)
{}

PixelVector PixelRect::getPosition() const
{
	return position;
}

PixelVector PixelRect::getSize() const
{
	return size;
}

int PixelRect::getLeft() const
{
	return getPosition().x;
}

int PixelRect::getRight() const
{
	return getPosition().x + getSize().x;
}

int PixelRect::getTop() const
{
	return getPosition().y;
}

int PixelRect::getBot() const
{
	return getPosition().y + getSize().y;
}

bool PixelRect::operator==(const PixelRect& rect)
{
	return rect.getPosition() == getPosition() && rect.getSize() == getSize();
}

std::string PixelRect::toString() const
{
	return "PR(" + getPosition().toString() + ", " + getSize().toString() + ")";
}
