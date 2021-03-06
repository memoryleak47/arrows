#include "CompressBuffer.hpp"

#include <misc/Converter.hpp>
#include <misc/Debug.hpp>

#include <network/packets/LoginPacket.hpp>
#include <network/packets/LockPacket.hpp>
#include <network/packets/AvatarPacket.hpp>
#include <network/packets/SkillPacket.hpp>
#include <network/packets/ItemPacket.hpp>
#include <network/packets/TeamPacket.hpp>
#include <network/packets/DisconnectPacket.hpp>
#include <network/packets/LobbyPlayersPacket.hpp>
#include <network/packets/MapPacket.hpp>
#include <network/packets/PacketWithID.hpp>
#include <network/packets/ChangeActionsPacket.hpp>
#include <network/packets/GameStartPacket.hpp>
#include <controller/PlayerController.hpp>
#include <entity/TestKiste.hpp>
#include <avatar/game/Archer.hpp>
#include <avatar/game/Rogue.hpp>
#include <entity/bullets/SimpleArrow.hpp>
#include <entity/EntityGivethrough.hpp>
#include <collision/RectShape.hpp>
#include <collision/RotatedRectShape.hpp>
#include <collision/CircleShape.hpp>

#include <player/LobbyPlayer.hpp>

CompressBuffer::CompressBuffer(const std::string& s)
	: counter(0)
{
	this->string = s;
}

std::string CompressBuffer::cutString()
{
	return cut(cutInt());
}

int CompressBuffer::cutInt()
{
	std::string s = cut(4);
	return (((unsigned char) s[0]) << 24)
		+ (((unsigned char) s[1]) << 16)
		+ (((unsigned char) s[2]) << 8)
		+ (unsigned char)s[3];
}

float CompressBuffer::cutFloat()
{
	static_assert(sizeof(int) == sizeof(float), "cutFloat() doesn't work");

	int i = cutInt();
	return *reinterpret_cast<float*>(&i);
}

char CompressBuffer::cutChar()
{
	std::string tmp = cut(1);
	return tmp[0];
}

short CompressBuffer::cutShort()
{
	std::string s = cut(2);
	return (((unsigned char) s[0]) << 8) + ((unsigned char) s[1]);
}

bool CompressBuffer::cutBool()
{
	std::string tmp = cut(1);
	return tmp[0] == '1';
}

long CompressBuffer::cutLong()
{
	union
	{
		char b[sizeof(long)];
		long l;
	} tmp;
	std::string s = cut(sizeof(long));
	for (unsigned int i = 0; i < sizeof(long); i++)
	{
		tmp.b[i] = s.c_str()[i];
	}
	return tmp.l;
}

std::vector<std::vector<TileID>> CompressBuffer::cutMap()
{
	int width = cutInt();
	int height = cutInt();

	std::vector<std::vector<TileID>> map;

	for (int y = 0; y < height; y++)
	{
		map.push_back(std::vector<TileID>());
		for (int x = 0; x < width; x++)
		{
			map.back().push_back((TileID) cutChar());
		}
	}
	return map;
}

Compressable* CompressBuffer::cutByCompressID(CompressID cid)
{
	switch (cid)
	{
		#define X(name, cid) case CompressIDs::cid: return new name(this);
		#define Y(name, cid) case CompressIDs::cid: return new name(this);
		#include "CompressID.list"
		#undef X
		#undef Y
		default:
			Debug::warn("no Compressable with CompressID=" + Converter::intToString((int)cid));
			return nullptr;
	}
}

std::vector<void*> CompressBuffer::cutVectorByCompressID(CompressID cid)
{
	int size = cutInt();
	std::vector<void*> vec;
	for (int i = 0; i < size; i++)
	{
		vec.push_back(cutByCompressID(cid));
	}
	return vec;
}

std::string CompressBuffer::cut(int amount)
{
	counter += amount;
	return string.substr(counter-amount, amount);
}
