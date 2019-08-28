#pragma once
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "texture.h"
extern const float G_xcord[8];
extern const float G_ycord[8];
class board
{
private:
	sf::RectangleShape square;
	sf::RectangleShape square_path;
	
	int id;
	int x_cord;
	int y_cord;
	void position(int black, int white);


public:
	board(int color, int id_loop);
	sf::RectangleShape &display();
	sf::RectangleShape & display_path();
	sf::Vector2i cord();
};
