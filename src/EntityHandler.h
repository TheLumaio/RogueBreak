#pragma once

#include <vector>
#include "Item.h"

class Item;

struct Capsule {
	int x;
	int y;
	Item* h;
	Capsule(int x, int y, Item* h) {
		this->x = x;
		this->y = y;
		this->h = h;
	}
};

/// Singleton
class EntityHandler 
{
public:
	static EntityHandler* getInstance();
	std::vector<Capsule*>& getEntities();
	void addEntity(Capsule*);
private:

	std::vector<Capsule*> entities;
	static EntityHandler* _instance;
	EntityHandler() {}
public:
	EntityHandler(EntityHandler const&)=delete;
	void operator=(EntityHandler const&)=delete;
};
