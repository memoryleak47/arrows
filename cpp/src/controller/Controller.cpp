#include "Controller.hpp"

#include <misc/compress/CompressBuffer.hpp>

Controller::Controller(CompressBuffer* buffer)
	: actions((Actions) buffer->cutChar())
{}

Actions Controller::getActions() const
{
	return actions;
}

std::string Controller::getCompressString() const
{
	std::string s;
	return s + ((char) actions);
}

void Controller::setActions(const Actions acts)
{
	this->actions = acts;
}
