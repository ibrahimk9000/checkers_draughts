#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <SFML/Window.hpp>
#include <iostream>
#include "texture.h"

#include "board.h"
#include "players.h"
#include "stdint.h"

class Game
{

private:
	sf::Event event;
	sf::RectangleShape finish;
	sf::RenderWindow window;
	player playerone;
	player playertwo;
	std::vector<board> boardblack;
	std::vector<board> boardwhite;
	sf::Text txt;
	sf::Font font;
	void draw();
	bool events();
	player &turn();
	player & notmyturn();
	void swap();
public:
	Game();
	void boardinit();
	void playerinit();
	void endblackrectangle();
	bool initfont();
	bool run();
	
};