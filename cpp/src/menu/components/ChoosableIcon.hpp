#ifndef __CHOOSABLEICON_CLASS__
#define __CHOOSABLEICON_CLASS__

#include "Icon.hpp"

class LobbyPlayer;
class LobbyMenu;

class ChoosableIcon : public Icon
{
	public:
		ChoosableIcon(LobbyPlayer*, LobbyMenu*, ComponentContainer*, const PixelRect&);
		virtual void render() const override;
		bool isChoosable() const;
		virtual int getChoosePhase() const = 0;
	protected:
		LobbyPlayer* getPlayer() const;
		LobbyMenu* getLobbyMenu() const;
	private:
		LobbyPlayer* player;
		LobbyMenu* lobby;

};

#include "../../player/LobbyPlayer.hpp"
#include "../menues/LobbyMenu.hpp"

#endif
