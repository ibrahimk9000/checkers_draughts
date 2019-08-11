
#pragma once
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "board.h"

#define PAWN_NUMBER 12
#define PLAYER_ONE 0
#define PLAYER_TWO 5
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
	pawns(int redorblue, sf::Texture * texture, sf::Texture * text);
	std::vector<path> path_pawnn;
	sf::CircleShape &display();
	sf::RectangleShape & displayborder();
	
	int get_id();
	pawnmove &struct_id();
	void position(int offsetblue, int offsetred);
	void move(int movex,int movey);
	void select( int x, int y);
	void resetmove();
	void moveforward(sf::Vector2i coor);
	void dell();
	sf::Vector2i cord();
	void setking(bool value);
	bool kings();

	bool path_pawn(path s);


	
	
	//void symmetry();


};