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
	sf::RenderWindow window;
	player playerone;
	player playertwo;
	std::vector<board> boardblack;
	std::vector<board> boardwhite;

public:
	Game();
	void run();
	void draw();
	void events();
	player &turn();
	player & notmyturn();
	void swap();
};