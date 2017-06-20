#include "Playstate.h"
#include "GenericFood.h"

Playstate::Playstate() :
	player(),
	mode(WORLD),
	cursor(0, 0)
	//savegame("savegame.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
	font.loadFromFile("creep2.bdf");
	const sf::Texture& tex = font.getTexture(16);
	const_cast<sf::Texture&>(tex).setSmooth(false);

	text.setCharacterSize(11);
	text.setFont(font);

	player.setHunger(100);
	player.setPosition(256, 256);
	
	highlight.setFillColor(sf::Color(25, 25, 25, 255));

	EntityHandler::getInstance()->getEntities().push_back(new Capsule(265, 260, new Door));
	EntityHandler::getInstance()->getEntities().push_back(new Capsule(250, 260, new GenericFood));

	//snack.printLocals();

	//world.save(savegame);
}

void Playstate::update(float dt) {
	world.update(dt);
}

void Playstate::render(sf::RenderWindow* window) {

	static float GOLD = 32*12+5;

	
	/// Highlight
	// fill
	switch (mode)
	{
	case WORLD:
		highlight.setPosition(10, 5);
		highlight.setSize({GOLD*2, 720-10});
		break;
	case INVENTORY:
		highlight.setPosition(GOLD*2+10, 5);
		highlight.setSize({250, GOLD});
		break;
	default:
		break;
	}
	highlight.setFillColor(sf::Color(25, 25, 25, 255));
	window->draw(highlight);

	// outline
	highlight.setFillColor({0, 0, 0, 0});
	highlight.setOutlineColor({25, 25, 25, 255});
	highlight.setOutlineThickness(1);
	
	// world
	highlight.setPosition(10, 5);
	highlight.setSize({GOLD*2, 720-10});
	window->draw(highlight);
	// inventory
	highlight.setPosition(GOLD*2+10, 5);
	highlight.setSize({250, GOLD});
	window->draw(highlight);
	// player stats
	highlight.setPosition(GOLD*2+260, 5);
	highlight.setSize({1280-(GOLD*2+265), GOLD});
	window->draw(highlight);
	// output
	highlight.setPosition(GOLD*2+10, GOLD+5);
	highlight.setSize({GOLD, 720-GOLD-10});
	window->draw(highlight);
	highlight.setOutlineThickness(0);


	/// WORLD
	world.render(window, player.getPosition(), text, output, mode==EDITOR);
	
	//world.renderPreview(window, text);

	/// INVENTORY
	text.setPosition(GOLD*2+20, 5);
	text.setFillColor(sf::Color(155, 155, 200, 255));
	text.setString("Inventory");
	window->draw(text);
	text.setFillColor(sf::Color(200, 200, 200, 255));
	int i=0;
	for (auto hackable : player.getInventory())
	{
		if (i == index && mode == INVENTORY) {
			highlight.setFillColor(sf::Color(75, 75, 75, 255));
			highlight.setPosition(GOLD*2+25, 20+i*16+3);
			highlight.setSize({200, 16});
			window->draw(highlight);
		}
		text.setString(hackable->getName());
		text.setPosition(GOLD*2+30, 24+i*16);
		window->draw(text);
		i++;
	}

	/// Output
	text.setPosition(GOLD*2+15, GOLD+8);
	text.setFillColor({155, 155, 200, 255});
	text.setString("Output");
	window->draw(text);

	if (output.size() > 20) output.erase(output.begin());

	for (int i = 0; i < output.size(); i++) {
		text.setPosition(GOLD*2+30, GOLD+20+i*12);
		text.setString(output[i]);
		text.setFillColor({155, 200, 200});
		window->draw(text);
	}

	/// Health and other player stats

	text.setPosition(GOLD*2+270, 5);
	text.setFillColor(sf::Color(155, 155, 200, 255));
	text.setString("Character");
	window->draw(text);

	text.setFillColor(sf::Color(200, 200, 200, 255));
	std::string bars;
	for (int i = 0; i < ceil(player.getHealth()/100)*10; i++) { bars += '-'; }
	char hpbar[32];
	sprintf(hpbar, "Health [%10s] %d", bars.c_str(), player.getHealth());
	text.setString(std::string(hpbar));
	text.setPosition(GOLD*2+280, 20);
	window->draw(text);

	bars.clear();
	for (int i = 0; i < ceil(player.getThirst()/100)*10; i++) { bars += '-'; }
	sprintf(hpbar, "Thirst [%10s] %d", bars.c_str(), player.getThirst());
	text.setString(std::string(hpbar));
	text.setPosition(GOLD*2+280, 40);
	window->draw(text);

	bars.clear();
	for (int i = 0; i < ceil(player.getHunger()/100)*10; i++) { bars += '-'; }
	sprintf(hpbar, "Hunger [%10s] %d", bars.c_str(), player.getHunger());
	text.setString(std::string(hpbar));
	text.setPosition(GOLD*2+280, 60);
	window->draw(text);


	renderPauseMenu(window);

}

void Playstate::keypressed(sf::Keyboard::Key key) {
	if (PauseMenu_isPaused) {
		keyPressedPauseMenu(key);
		return;
	}

	if (key == sf::Keyboard::Q) {
		PauseMenu_isPaused = true;
	}

	if (key == sf::Keyboard::Tab && mode<2) {
		mode = (MODE)((mode+1)%2);
	}
	if (mode == WORLD) {
		if (key == sf::Keyboard::Up    && player.getPosition().y > 0  ) player.move( 0, -1, &world, output);
		if (key == sf::Keyboard::Down  && player.getPosition().y < 512) player.move( 0,  1, &world, output);
		if (key == sf::Keyboard::Left  && player.getPosition().x > 0  ) player.move(-1,  0, &world, output);
		if (key == sf::Keyboard::Right && player.getPosition().x < 512) player.move( 1,  0, &world, output);

		/// Other

		if (key == sf::Keyboard::E) {
			Item* h = player.findItem();
			if (h != nullptr) {
				h->onActivate(output, player);
			}
		}
		if (key == sf::Keyboard::G) {
			Item* h = world.itemAtPos(player.getPosition().x, player.getPosition().y);
			if (h != nullptr) h->onPickup(player);
		}
	}
	else if (mode == INVENTORY) {
		if (key == sf::Keyboard::Down) {
			index = (index+1)%player.getInventory().size();
		}
		else if (key == sf::Keyboard::Up) {
			index = mod(index-1, player.getInventory().size());
		}
		else if (key == sf::Keyboard::E) {
			player.getInventory()[index]->onActivate(output, player);
		}
	}
}

void Playstate::textentered(char c) {
	if (skip) {
		skip=false;
		return;
	}
	if (mode == EDITOR) {
		if (isalnum(c) || isspec(c)) {
			lines[cursor.y].insert(cursor.x, 1, c);
			cursor.x++;
		}
	}
}

