#pragma once
#include "texture.h"
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
class player;
extern const float x[8];
extern const float y[8];
class board
{
private:
	sf::RectangleShape square;
	sf::RectangleShape square_path;
	static int id_b;
	static int id_w;
	int id;
	int x_cord;
	int y_cord;
		
public:
	//friend void lightpath(int idd);
	//board(int color, sf::Texture *texture);
	void position(int black, int white);
	board(int color, sf::Texture * texture, sf::Texture * text);
	sf::RectangleShape &display();
	sf::RectangleShape & display_path();
	sf::Vector2i cord();
};
