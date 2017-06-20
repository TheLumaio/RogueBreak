#include "Player.h"

Player::Player(std::string name) :
	health(100),
	thirst(0),
	hunger(0),
	tiredness(0),
	odx(0),
	ody(0)
{
	this->name=name;
}

int Player::getHealth    () { return health;    }
int Player::getThirst    () { return thirst;    }
int Player::getHunger    () { return hunger;    }
int Player::getTiredness () { return tiredness; }

std::string Player::getName() { return name; }

void Player::setHealth    (int set) { health    = set; }
void Player::setThirst    (int set) { thirst    = set; }
void Player::setHunger    (int set) { hunger    = set; }
void Player::setTiredness (int set) { tiredness = set; }

sf::Vector2i Player::getPosition()             { return position;               }
void         Player::setPosition(int x, int y) { position.x = x; position.y = y;}

void Player::move(int dx, int dy, Map* world, std::vector<std::string>& output) {
	if (position.x+dx < 0) dx = 0;
	if (position.y+dy < 0) dy = 0;
	if (position.x+dx > 511) dx=0;
	if (position.y+dy > 511) dy=0;
	odx = dx;
	ody = dy;

	int newpos = (int)world->checkTile(position.x+dx, position.y+dy);
	Item* item = world->itemAtPos(position.x+dx, position.y+dy);
	if (item == nullptr) item = new Item;
	if (newpos == WALL ||
		newpos == LOCKEDDOOR ||
		newpos == DEEPWATER ||
		item->getChar() == '+') {
		output.push_back("Can't move there");
		return;
	}

	position.x += dx;
	position.y += dy;

	if (dx < 0) output.push_back("Moved West");
	if (dx > 0) output.push_back("Moved East");
	if (dy < 0) output.push_back("Moved North");
	if (dy > 0) output.push_back("Moved South");
}

Item* Player::findItem()
{
	for (auto cap : EntityHandler::getInstance()->getEntities())
	{
		if (cap->x == position.x+odx && cap->y == position.y+ody)
			return cap->h;
	}
	return nullptr;
}

std::vector<Item*>& Player::getInventory()
{
	return inventory;
}


