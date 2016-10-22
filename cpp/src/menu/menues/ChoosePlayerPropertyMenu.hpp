#ifndef __CHOOSEPLAYERPROPERTYMENU_CLASS__
#define __CHOOSEPLAYERPROPERTYMENU_CLASS__

class LobbyMenu;
class PlayerPropertyUserPacket;
class PlayerProperty;
class PlayerPropertyIcon;

#include <menu/Menu.hpp>
#include <vector>

class ChoosePlayerPropertyMenu : public Menu
{
	public:
		ChoosePlayerPropertyMenu(LobbyMenu*, PlayerPropertyUserPacket*, const std::vector<PlayerProperty*>&);
		virtual ~ChoosePlayerPropertyMenu();
		PlayerPropertyIcon* getFirstVoidSlotIcon() const;
		std::vector<PlayerPropertyIcon*> getSlotIcons() const;
		LobbyMenu* getLobbyMenu() const;
		void okPressed();
		void chooseIconPressed(PlayerProperty*);
	private:
		LobbyMenu* lobby;
		PlayerPropertyUserPacket* slotPacket;
		const std::vector<PlayerProperty*> chooseProperties; // XXX memoryleak?
		std::vector<PlayerPropertyIcon*> slotIcons;
};

#endif
