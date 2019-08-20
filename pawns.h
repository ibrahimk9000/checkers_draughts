
#pragma once
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "texture.h"

extern const float G_xcord[8];
extern const float G_ycord[8];
struct pawnmove {
	int id;
	int x;
	int y;
	
};
struct path {
	pawnmove begin;
	pawnmove end;
	int  opponentid;
	int eatstatus;
};
class pawns
{

private:
	sf::CircleShape circle;
	int player_id;
	int status;
	sf::Vector2f mouseRectOffset;
	sf::Vector2f lastpos;
	bool king = false;
	int static id_rd;
	int id;
	int x_cord;
	int y_cord;
	int board;
	pawnmove id_cord;
	sf::RectangleShape squareborder;
public:
	pawnmove cfour;

	pawns(int redorblue, sf::Texture * texture, sf::Texture * text);
	std::vector<path> path_pawnn;
	sf::CircleShape &display();
	sf::RectangleShape & displayborder();
	
	int get_id();
	pawns(int redorblue);
	pawnmove &struct_id();
	void position(int offsetblue, int offsetred);
	void move(int movex,int movey);
	void select( int x, int y);
	void resetmove();
	void moveforward(sf::Vector2i coor);
	void transform();
	void dell();
	sf::Vector2i cord();
	void setking(bool value);
	bool kings();

	bool path_pawn(path s);
};