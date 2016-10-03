#include "GameRect.hpp"

GameRect::GameRect(float x, float y, float w, float h) : position(x, y), size(w, h)
{}

GameRect::GameRect(const GameRect& rect) : position(rect.getPosition()), size(rect.getSize())
{}

GameRect::GameRect(const GameVector& position, const GameVector& size) : position(position), size(size)
{}

GameVector GameRect::getPosition() const
{
	return position;
}

GameVector GameRect::getSize() const
{
	return size;
}

float GameRect::getLeft() const
{
	return getPosition().x;
}

float GameRect::getRight() const
{
	return getPosition().x + getSize().x;
}

float GameRect::getTop() const
{
	return getPosition().y;
}

float GameRect::getBot() const
{
	return getPosition().y + getSize().y;
}

float GameRect::getWidth() const { return getRight() - getLeft(); }
float GameRect::getHeight() const { return getBot() - getTop(); }

bool GameRect::collidesWith(const GameRect& r) const
{
	return     getLeft() <= r.getRight()
		&& getRight() >= r.getLeft()
		&& getTop() <= r.getBot()
		&& getBot() >= r.getTop();
}

bool GameRect::operator==(const GameRect& rect)
{
	return rect.getPosition() == getPosition() && rect.getSize() == getSize();
}

std::string GameRect::toString() const
{
	return "GR(" + getPosition().toString() + ", " + getSize().toString() + ")";
}
