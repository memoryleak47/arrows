#include "LockUserPacket.hpp"

LockUserPacket::LockUserPacket(bool locked) : locked(locked)
{}

bool LockUserPacket::isLocked() const
{
	return locked;
}

std::string LockUserPacket::toString() const
{
	return compressBool(isLocked());
}

CID LockUserPacket::getCID() const
{
	return LOCK_USER_PACKET_CID;
}
