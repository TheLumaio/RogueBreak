#include "EntityHandler.h"

EntityHandler* EntityHandler::getInstance() {
	if (!_instance)
		_instance = new EntityHandler();
	return _instance;
}

std::vector<Capsule*>& EntityHandler::getEntities() {
	return entities;
}

void EntityHandler::addEntity(Capsule* cap) {
	entities.emplace_back(cap);
}

EntityHandler *EntityHandler::_instance = 0;
