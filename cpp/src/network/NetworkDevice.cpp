#include "NetworkDevice.hpp"

#include <misc/Global.hpp>
#include <network/Packet.hpp>
#include <core/Main.hpp>
#include "NetworkInterface.hpp"
#include <SFML/Network/Packet.hpp>

NetworkDevice::NetworkDevice()
{
	socket.setBlocking(false);
	socket.bind(PORT);
}

void NetworkDevice::send(Packet* packet, const sf::IpAddress& ip)
{
	if (packet == nullptr)
	{
		Debug::warn("NetworkDevice::send(): packet is null");
	}

	sf::Packet sfmlPacket;
	std::string string = packet->compress();
	sfmlPacket << string;

	if (socket.send(sfmlPacket, ip, PORT) != sf::Socket::Done) // send
	{
		Debug::warn("NetworkDevice::send() failed");
	}
	else
	{
		if (global::PACKET_SOUND)
		{
			#ifndef OS_WINDOWS
				system("paplay /usr/share/sounds/ubuntu/notifications/Blip.ogg &");
			#else
				Debug::warn("Your OS doesn't support packet sound");
			#endif
		}

		if (string.length() > global::MAX_SHOWN_PACKET_SIZE)
		{
			if (TAG_NETWORK) Debug::note("sent big packet with CompressID: " + Converter::intToString(string[0]));
		}
		else
		{
			if (TAG_NETWORK) Debug::note("sent packet with string: " + Converter::charsToString(string));
		}
	}

	sfmlPacket.clear();
}

void NetworkDevice::receive()
{
	sf::Packet sfmlPacket;
	sf::IpAddress ip;
	unsigned short port;
	if (socket.receive(sfmlPacket, ip, port) != sf::Socket::Done)
	{
		return;
	}

	if (global::PACKET_SOUND)
	{
		#ifndef OS_WINDOWS
			system("paplay /usr/share/sounds/ubuntu/stereo/message.ogg &");
		#else
			Debug::warn("Your OS doesn't support packet sound");
		#endif
	}

	std::string string;
	sfmlPacket >> string;

	if (string.length() > global::MAX_SHOWN_PACKET_SIZE)
	{
		if (TAG_NETWORK) Debug::note("received big packet with CompressID: " + Converter::intToString(string[0]));
	}
	else
	{
		if (TAG_NETWORK) Debug::note("received packet with string: " + Converter::charsToString(string));
	}

	Packet* packet = (Packet*) Compressable::decompress(string); // XXX choose different cast

	if (packet == nullptr)
	{
		delete packet;
		Debug::error("NetworkDevice::receive(): decompression or conversion to Packet* failed");
		return;
	}

	if (interfaceStack.empty())
	{
		delete packet;
		Debug::warn("NetworkDevice::receive(): interfaceStack is empty");
		return;
	}

	getNetworkInterface()->receivePacket(packet, ip);
}

NetworkInterface* NetworkDevice::getNetworkInterface() const
{
	return interfaceStack.top();
}

void NetworkDevice::pushInterface(NetworkInterface* interface)
{
	interfaceStack.push(interface);
}

void NetworkDevice::popInterface()
{
	interfaceStack.pop();
}
