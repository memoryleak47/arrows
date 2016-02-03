#ifndef __MAPPACKET_CLASS__
#define __MAPPACKET_CLASS__

#include <vector>

#include "../Packet.hpp"

class MapPacket : public Packet
{
	private:
		std::vector<std::vector<int>> map; // Zweidimensionaler Vektor lol
};

#endif