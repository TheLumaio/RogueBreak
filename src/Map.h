#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <sstream>
#include "EntityHandler.h"
#include "Simplex.h"
#include "Item.h"

class Item;

struct fcolor {
	float r,g,b,a;
	fcolor() { r=1;g=1;b=1;a=1; }
	fcolor(float r,  float g, float b, float a = 1.f) :
		r(r),
		g(g),
		b(b),
		a(a)
	{}
};

class Light {
public:
	fcolor color;
	sf::Vector2i position;
	int radius;
	Light(fcolor c, sf::Vector2i pos, int rad = 10) :
		color(c),
		position(pos),
		radius(rad)
	{}
};

enum TILE
{
	GROUND,
	WALL,
	DOOR,
	LOCKEDDOOR,
	WATER,
	DEEPWATER,
	FLOOR,
	TREE
};


struct Tile {
	TILE type;
	bool visible;
	bool discovered;
	fcolor color;
	Tile(TILE t=WALL, bool v=false, fcolor c={1, 1, 1}) {
		type=t;
		visible=v;
		color=c;
	}
};

class Map
{
private:
	Tile map[512][512];
	sf::Vector2i camera;
	const char* table = "!@#$%^&*{}[]|\\><,.?/";
	std::vector<Light> lights;
	float timer;

public:
	Map();
	
	void update(float);
	void render(sf::RenderWindow* window, sf::Vector2i player, sf::Text& text, std::vector<std::string>& output, bool matrix=false);
	void renderPreview(sf::RenderWindow* window, sf::Text& text);

	//void save(SQLite::Database& db);

	inline TILE checkTile(int x, int y) { return (TILE)map[x][y].type; }

	Item* itemAtPos(int x, int y);

};
