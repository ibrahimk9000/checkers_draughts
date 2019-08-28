#include "board.h"


		

texture black_board_texture("black.png");    // load texture
texture white_board_texture("white.png");
texture border("frame.png");



board::board(int color,int id_loop) {

	square = sf::RectangleShape(sf::Vector2f(100, 100));   //inisitalise rectangle 100x100 for barod case 
	id = id_loop;  // id of board
	
	if (color == 0) // if 0 the barod is white
	{
		square.setTexture(white_board_texture.map());
	
	
	position(0, 1);
    }
	if (color == 1) // if 1 the board is black
	{
		square.setTexture(black_board_texture.map());
	
	square_path = sf::RectangleShape(sf::Vector2f(100, 100));  //create texture that surround board case when pawn selected 
	square_path.setTexture(border.map());
	//square_path.setFillColor(sf::Color())
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
	square.setPosition(G_xcord[x_cord], G_ycord[y_cord]);
	
    }
	else 
	{
	x_cord = id % 4 * 2 + black;
	y_cord = id / 4;
	square.setPosition(G_xcord[x_cord], G_ycord[y_cord]);
	
	}
	if (black == 1)
		square_path.setPosition(G_xcord[x_cord], G_ycord[y_cord]);
}
			
sf::Vector2i board::cord()
{
	return sf::Vector2i(x_cord, y_cord);
}








				
				

