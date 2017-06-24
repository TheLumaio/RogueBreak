#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

extern bool PauseMenu_isPaused;
extern sf::RenderWindow* PauseMenu_windowRef;
extern sf::RectangleShape PauseMenu_rect;
extern sf::Font PauseMenu_font;

void updatePauseMenu(float);
void renderPauseMenu(sf::RenderWindow*, sf::Text&);
void keyPressedPauseMenu(sf::Keyboard::Key); 

#endif

