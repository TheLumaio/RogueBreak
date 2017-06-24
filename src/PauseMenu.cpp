#include "PauseMenu.h"

bool PauseMenu_isPaused = false;
sf::RenderWindow* PauseMenu_windowRef = nullptr;
sf::RectangleShape PauseMenu_rect;
sf::Font PauseMenu_font;

void updatePauseMenu(float dt)
{
}

void renderPauseMenu(sf::RenderWindow* window, sf::Text& PauseMenu_text)
{
	if (PauseMenu_windowRef == nullptr) {
		PauseMenu_windowRef = window;
		PauseMenu_font.loadFromFile("creep2.bdf");
		PauseMenu_text.setFont(PauseMenu_font);
		PauseMenu_text.setCharacterSize(11);
	}
	if (!PauseMenu_isPaused) return;

	sf::Vector2u winSize = window->getSize();

	// Confirmation offset
	winSize.x -= 495;

	// Backdrop
	PauseMenu_rect.setPosition(sf::Vector2f(0, 0));
	PauseMenu_rect.setSize(sf::Vector2f(winSize.x, winSize.y));

	PauseMenu_rect.setFillColor(sf::Color(100, 100, 100, 140));

	window->draw(PauseMenu_rect);


	// Confirmation box
	PauseMenu_rect.setPosition(sf::Vector2f(winSize.x/2-300/2, winSize.y/2-100/2));
	PauseMenu_rect.setSize(sf::Vector2f(300, 100));

	PauseMenu_rect.setFillColor(sf::Color(25, 25, 25));

	window->draw(PauseMenu_rect);

	// Confirmation text
	PauseMenu_text.setFillColor(sf::Color(255, 255, 255));
	PauseMenu_text.setString("Are you sure you want to quit?");
	PauseMenu_text.setPosition(
		sf::Vector2f(floor(winSize.x/2-PauseMenu_text.getLocalBounds().width/2), winSize.y/2-25)
	);

	window->draw(PauseMenu_text);

	// Confirmation "Yes"
	PauseMenu_text.setString("[Y]es");
	PauseMenu_text.setPosition(sf::Vector2f(floor(winSize.x/2-50), winSize.y/2));
	PauseMenu_text.setFillColor(sf::Color(155, 100, 100));

	window->draw(PauseMenu_text);

	// Confirmation "No"
	PauseMenu_text.setString("[N]o");
	PauseMenu_text.setPosition(sf::Vector2f(floor(winSize.x/2+35), winSize.y/2));

	window->draw(PauseMenu_text);

}

void keyPressedPauseMenu(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Y && PauseMenu_windowRef != nullptr) {
		PauseMenu_windowRef->close();
		return;
	}
	if (key == sf::Keyboard::N && PauseMenu_windowRef != nullptr) {
		PauseMenu_isPaused = false;
		return;
	}
}
