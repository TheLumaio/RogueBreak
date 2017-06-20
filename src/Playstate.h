//#pragma warning(disable : 4267 4244)

#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include "ProgrammingGame.h"
#include "Map.h"
#include "Player.h"
#include "Door.h"
#include "PauseMenu.h"

class Map;

enum MODE
{
	WORLD,
	INVENTORY,
	EDITOR
};

static bool isspec(char& c) {
	static std::string chars = "!@#$%%^&*()_+-=[]{}\\|;:'\",<.>/?`~ \t";
	if (std::find(chars.begin(), chars.end(), c) == chars.end())
		return false;
	return true;
}

static int mod(int x, int m) {
	int r = x%m;
	return r<0 ? r+m : r;
}

// thanks to: http://ysonggit.github.io/coding/2014/12/16/split-a-string-using-c.html
static std::vector<std::string> split(const std::string &s, char delim) {
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> tokens;
	while (getline(ss, item, delim)) {
		tokens.push_back(item);
	}
	return tokens;
}

class Playstate : public Gamestate
{
private:
	Player player;
	sf::Font font;
	sf::Text text;
	sf::RectangleShape highlight;

	MODE mode;

	// map
	Map world;

	// inv
	int index;

	// editor
	int cindex;
	sf::Vector2i cursor;
	std::string code;
	std::string error;
	std::vector<std::string> lines;
	bool skip; // Skip the next textinput call

	// database for saving/loading
	//SQLite::Database savegame;

	// output
	std::vector<std::string> output;

public:
	Playstate();

	void update(float) override;

	// my sanity is running thin. send help.
	void render(sf::RenderWindow* window) override;

	void keypressed(sf::Keyboard::Key key) override;

	void textentered(char c) override;

};
