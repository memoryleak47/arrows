#ifndef __CONTROLLER_CLASS__
#define __CONTROLLER_CLASS__

class Mob;

enum Action
{ GO_LEFT, GO_RIGHT, JUMP, SKILL1, SKILL2, SKILL3, SKILL4 };

typedef char Actions;

class Controller
{
	public:
		virtual ~Controller() {}
		Actions getActions() const;
		bool getAction(Action) const;
	protected:
		void setAction(Action, bool);
	private:
		void setActions(const Actions); // Setzt Actions auf das übergebene
		virtual bool updateActions(); // schaut ob sich etwas verändert hat, und updated diese nach aktuellen Key-Status
		Actions actions;
	friend class GameInterface;
	friend class GamePlayer;
};

#include <game/GameInterface.hpp>
#include <player/GamePlayer.hpp>
#include <entity/Mob.hpp>

#endif