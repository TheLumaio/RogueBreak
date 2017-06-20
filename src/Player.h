#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Item.h"

class Item;
class Map;

class Player
{
private:
	std::string name;
	int health;
	int thirst;
	int hunger;
	int tiredness;

	sf::Vector2i position;
	std::vector<Item*> inventory;

	int odx,ody;

public:
	Player(std::string name="Default");

	int getHealth    ();
	int getThirst    ();
	int getHunger    ();
	int getTiredness ();

	std::string getName();

	void setHealth    (int set);
	void setThirst    (int set);
	void setHunger    (int set);
	void setTiredness (int set);

	sf::Vector2i getPosition();
	void         setPosition(int x, int y);

	void move(int dx, int dy, Map* world, std::vector<std::string>& output);
	Item* findItem();

	std::vector<Item*>& getInventory();

};
