#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class ProgrammingGame;

class Gamestate
{
public:
	virtual ~Gamestate(){}
	virtual void update(float){}
	virtual void render(sf::RenderWindow*){}
	virtual void keypressed(sf::Keyboard::Key){}
	virtual void keyreleased(sf::Keyboard::Key){}
	virtual void mousepressed(int, int, sf::Mouse::Button){}
	virtual void mousereleased(int, int, sf::Mouse::Button){}
	virtual void resized(int, int){}
	virtual void textentered(char){}
};

class ProgrammingGame
{
public:
	sf::RenderWindow* m_renderwindow;

	ProgrammingGame()=default;

	void init() {
		m_renderwindow = new sf::RenderWindow(sf::VideoMode(1280, 720), "Programming Game", sf::Style::Close);
	}

	void start() {
		std::cout << "TIME/SEED: " << time(NULL) << std::endl;
		sf::Clock deltaclock;
		float deltatime=1.f/60.f;
		while (m_renderwindow->isOpen()) {
			sf::Event e;
			while (m_renderwindow->pollEvent(e)) {
				switch (e.type)
				{
				case sf::Event::KeyPressed:
					if (m_states.size()>0 && m_states[m_id]!=nullptr) m_states[m_id]->keypressed(e.key.code);
					break;
				case sf::Event::KeyReleased:
					if (m_states.size()>0 && m_states[m_id]!=nullptr) m_states[m_id]->keyreleased(e.key.code);
					break;
				case sf::Event::MouseButtonPressed:
					if (m_states.size()>0 && m_states[m_id]!=nullptr) m_states[m_id]->mousepressed(e.mouseButton.x, e.mouseButton.y, e.mouseButton.button);
					break;
				case sf::Event::MouseButtonReleased:
					if (m_states.size()>0 && m_states[m_id]!=nullptr) m_states[m_id]->mousereleased(e.mouseButton.x, e.mouseButton.y, e.mouseButton.button);
					break;
				case sf::Event::Resized:
					if (m_states.size()>0 && m_states[m_id]!=nullptr) m_states[m_id]->resized(e.size.width, e.size.height);
					break;
				case sf::Event::TextEntered:
					if (m_states.size()>0 && m_states[m_id]!=nullptr) m_states[m_id]->textentered((char)e.text.unicode);
					break;
				case sf::Event::Closed:
					m_renderwindow->close();
					break;
				default:
					break;
				}
			}

			if (m_states.size()>0 && m_states[m_id]!=nullptr) m_states[m_id]->update(deltatime);
			m_renderwindow->clear(sf::Color(0, 0, 0, 255));
			if (m_states.size()>0 && m_states[m_id]!=nullptr) m_states[m_id]->render(m_renderwindow); //m_states[m_id]->render(*m_renderwindow);//
			m_renderwindow->display();

			deltatime = deltaclock.restart().asSeconds();
			m_renderwindow->setTitle(std::string("DELTA: ") + std::to_string(deltatime));
		}
	}

	void change_state(std::string id, Gamestate* state=nullptr) {
		if (m_states[id] != nullptr) m_id = id;
		else {
			m_states[id] = state;
			m_id = id;
		}
	}

private:
	std::string m_id;
	Gamestate* m_stateref;
	std::map<std::string, Gamestate*> m_states;
};