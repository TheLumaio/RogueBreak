#pragma once

#include <iostream>
#include "Player.h"

class Player;

class Item
{
private:
	std::string name;
public:
	Item()=default;
	virtual ~Item()=default;

	virtual std::string getName () { return "ITEM"; }
	virtual char        getChar () { return 'H';    }
	virtual bool        isStatic() { return false;  }
	virtual void        onPickup(Player& p);
	virtual void        onActivate(
		std::vector<std::string>&,
		Player&
	) {}

};
