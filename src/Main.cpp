//#define SFML_STATIC
#include <iostream>
//#include <chaiscript/chaiscript.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include "ProgrammingGame.h"
#include "Playstate.h"

int main(int argc, char** argv)
{

	srand((unsigned int)time(NULL));

	ProgrammingGame game;
	game.init();
	game.change_state("playstate", new Playstate);

	game.start();

}
