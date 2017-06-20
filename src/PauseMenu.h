#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

extern bool PauseMenu_isPaused;
extern sf::RenderWindow* PauseMenu_windowRef;
extern sf::RectangleShape PauseMenu_rect;
extern sf::Font PauseMenu_font;
extern sf::Text PauseMenu_text;

void updatePauseMenu(float);
void renderPauseMenu(sf::RenderWindow*);
void keyPressedPauseMenu(sf::Keyboard::Key); 

#endif

