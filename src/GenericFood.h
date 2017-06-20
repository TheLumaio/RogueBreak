#pragma once

#include "Item.h"

class GenericFood : public Item
{
public:
	std::string getName() override { return "Generic Food"; }
	char getChar() override { return 'F'; }
	bool isStatic() override { return false; }
	void onActivate(std::vector<std::string>& out, Player& p) override { out.push_back("TODO: make food do shit"); }
};
