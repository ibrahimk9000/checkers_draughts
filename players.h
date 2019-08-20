#pragma once
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cstdlib>
#include <iostream>
#include "pawns.h"
#define PAWN_NUMBER 12
#define PLAYER_ONE 0
#define PLAYER_TWO 5
class player {

private:

	int indexxx;
	bool eatormove = false;
	path pathmove;
	pawnmove beginpath;
	pawnmove endpath;
	int base;
	int player_id;
	bool active_status;
	int magic;
	player *player2;
	int multieat=-1;
	int path_move;
	std::vector<int> banned;
public:
	std::vector<pawns> player_pawn;

	player(int plyr);

	player();
	player(int plyr, sf::Texture *texture, sf::Texture *text);
	int getplayer_id();
	void status(player * opp);
	int emptyright(pawnmove right, int eatflag=0);
	int emptyleft(pawnmove right, int eatflag=0);
	bool borderleft(pawnmove left, int eatflag=0);
	bool borderright(pawnmove right, int eatflag=0);
	bool movelegal(int indexx, sf::Vector2i coor);
	bool mv(int idd, sf::Vector2i coor);
	int multieatt();
	void movepawn(int i, sf::Vector2i cord);
	void deletepawn(int x);
	void enable(bool status);
	bool enabled();
	pawns & pawn(int index);
	std::vector<pawns>& vect_pawn();
	bool legalmove_id(int idd);
	void lightpath(int idd);
	bool  return_path(sf::Vector2i cord);
	void transform(int index);
	void erazemove(int i);
	bool rightright(pawnmove array_pawnn,bool bflag,int flag);
	bool leftleft(pawnmove array_pawnn, bool bflag, int flag);
	void increright(pawnmove & r);
	void increleft(pawnmove & r);
	bool eatright(pawnmove & r, int i);
	bool eatleft(pawnmove & r, int i);
	int auraright(pawnmove array_pawnn);
	int auraleft(pawnmove array_pawnn);
	bool checkbanned(int i);
};

