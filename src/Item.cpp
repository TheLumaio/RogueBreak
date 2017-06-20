#include "Item.h"
void Item::onPickup(Player& p)
{
	for (int i = 0; i < EntityHandler::getInstance()->getEntities().size(); i++)
	{
		if (EntityHandler::getInstance()->getEntities()[i]->h == this)
		{
			EntityHandler::getInstance()->getEntities().erase(EntityHandler::getInstance()->getEntities().begin()+i);
			break;
		}
	}
	p.getInventory().emplace_back(this);
}
