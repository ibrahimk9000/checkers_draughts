#include "board.h"

int board::id_b = 0;
int board::id_w = 0;
		
board::board(int color, sf::Texture *texture,sf::Texture *text=nullptr) {

	square = sf::RectangleShape(sf::Vector2f(100, 100));   //inisitalise rectangle 100x100 for barod case 
	square.setTexture(texture);
	
	if (color == 0) // if 0 the barod is white
	{
	id = id_w; // id of board
	++id_w;
	position(0, 1);
    }
	if (color == 1) // if 1 the board is black
	{
	id = id_b;
	++id_b;
	square_path = sf::RectangleShape(sf::Vector2f(100, 100));  //create texture that surround board case when pawn selected 
	square_path.setTexture(text);
	position(1, 0);
	
	}
	}
		
sf::RectangleShape &board::display() 
{
	return square; 
}
sf::RectangleShape &board::display_path()
{
	return square_path;
}
void board::position(int black, int white) 
{
	
	//make position of black and white board case

	if ((id/4) % 2 == 0) 
	{
	x_cord = id % 4 * 2 + white;  //white offset coordinate
	y_cord = id / 4;
	square.setPosition(x[x_cord], y[y_cord]);
	
    }
	else 
	{
	x_cord = id % 4 * 2 + black;
	y_cord = id / 4;
	square.setPosition(x[x_cord], y[y_cord]);
	
	}
	if (black == 1)
		square_path.setPosition(x[x_cord], y[y_cord]);
}
			
sf::Vector2i board::cord()
{
	return sf::Vector2i(x_cord, y_cord);
}








				
				

