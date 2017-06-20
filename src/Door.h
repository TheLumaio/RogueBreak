#pragma once
#include "Item.h"

class Door : public Item
{
private:
	bool locked;
public:
	Door() { locked=true; }

	std::string getName() override { return "DOOR"; }
	char getChar() override { return locked ? '+' : '-'; }
	bool isStatic() override { return true; }
	void onActivate(std::vector<std::string>& out, Player& p) override { locked=false; }

};
