#include "players.h"

player::player(int plyr, texture *tpawn,texture *tkpawn,texture *tborder) :player_id(plyr)
{
	  //initialise vector of pawns
		
		if (player_id == PLAYER_TWO)
		{
			for (int i = PAWN_NUMBER-1; i >= 0; --i)
				player_pawn.push_back(pawns(player_id, i,tpawn,tkpawn,tborder));

			base = 7; //board limit 
		}
		if (player_id == PLAYER_ONE) {
			for (int i = 0; i < PAWN_NUMBER; ++i)
			player_pawn.push_back(pawns(player_id,i,tpawn, tkpawn, tborder));

			base = 0; //board limit 
		}

	
}

player::player() {};

void player::status(player* opp)
{
	
	player2 = opp; //pointer to opponent player

	eatormove = false;
	
	erazemove(11);  //clear past move

	if (player_id == PLAYER_TWO)   //player two start from position 7 and player one stat form position 0
		magic = -1;
	if (player_id == PLAYER_ONE)
		magic = 1;
	//symmetry();
	for (int i = 0; i < PAWN_NUMBER; ++i)
	{
		if (multieat > 0 && multieat != i)
			continue;
		if ( player_pawn[i].struct_id().id < PAWN_NUMBER)
		{
			indexxx = i;
			if (player_pawn[i].king == true)
			{
				rightright( player_pawn[i].struct_id(), true);
				leftleft( player_pawn[i].struct_id(), true);

				magic = magic * (-1);

				rightright( player_pawn[i].struct_id(), true);
				leftleft( player_pawn[i].struct_id(), true);
				magic = magic * (-1);
				

			}
			else {
			//check pawns statis right and left path possibilities
				pawn_rightright( player_pawn[i].struct_id(), true);
				pawn_leftleft( player_pawn[i].struct_id(), true);
	         	}
		}
		
	}
	
}




int player::emptyright(pawnmove right,int eatflag) //eatflag can be 0 or 1 to add offset to eat
{
	for (int i = 0; i < PAWN_NUMBER; ++i)
	{
	
	if (right.x - magic-eatflag == player2-> player_pawn[i].struct_id().x && right.y + magic+eatflag == player2-> player_pawn[i].struct_id().y)
		return i;
	if (right.x - magic-eatflag ==  player_pawn[i].struct_id().x && right.y + magic+eatflag ==  player_pawn[i].struct_id().y )
		return -1;
	    
}
	return -2;
}
int player::emptyleft(pawnmove right,int eatflag)
{
	for (int i = 0; i < PAWN_NUMBER; ++i)
	{

		if (right.x + magic+eatflag == player2-> player_pawn[i].struct_id().x && right.y + magic+eatflag == player2-> player_pawn[i].struct_id().y)
			return i;
		if (right.x + magic+eatflag ==  player_pawn[i].struct_id().x && right.y + magic+eatflag ==  player_pawn[i].struct_id().y)
			return -1;
		
	}
	return -2;
}


bool player::borderleft(pawnmove left,int eatflag) 
{      
	if (left.x + magic+eatflag > 7 || left.x + magic + eatflag < 0 || left.y + magic+eatflag > 7 || left.y + magic + eatflag < 0)
		return false;

		return true;
}
bool player::borderright(pawnmove right,int eatflag) 
{
	if (right.x - magic-eatflag < 0 || right.x - magic - eatflag > 7 || right.y + magic+eatflag > 7 || right.y + magic + eatflag < 0)
		return false;

		return true;
}

bool player::movelegal(int idd,sf::Vector2i coor)
{

	multieat = -1;
	if (legalmove_id(idd) == true)	
		return mv(idd, coor);
	return false;
		
}
void player::olm(std::vector<path> &v, int idd)
{
	for (auto &elem : player_pawn[idd].path_pawn) {
		if (elem.first == true)
           v.push_back(elem);

	}
	}
	
	

bool player::mv(int idd, sf::Vector2i coor) {
	int x, y;
	int mag = 0;
	pawnmove begin, end;
	bool cs1 = false;
	bool cs2 = false;
	std::vector<path> moveonlythis;
	olm(moveonlythis, idd);
	
		for (auto &elem : moveonlythis)
		{
		
		
		if (elem.opponentid >= 0)
			mag = 1;
		
		if (elem.eatstatus.id == elem.begin.id)
		
			begin = elem.eatstatus;

		begin = elem.begin;
		end = elem.end;
		x = begin.x-end.x;
		y = begin.y - end.y;

		if (elem.eatstatus.id ==-1 ) {
			if (coor.x == elem.end.x && coor.y == elem.end.y)
			{
				if (elem.multi)
					multieat = idd;
				pathmove = elem;
				
				return true;

			}
			


		}
		
			if (elem.eatstatus.id == elem.begin.id)
			{
				begin = elem.eatstatus;
				if (x < 0) {
					if (coor.x > begin.x + mag && coor.x <= end.x)
						cs1 = true;
				}
				else {
					if (coor.x < begin.x - mag && coor.x >= end.x)
						cs1 = true;

				}
				if (y < 0) {
					if (coor.y > begin.y + mag && coor.y <= end.y)
						cs2 = true;
				}
				else {
					if (coor.y < elem.begin.y - mag && coor.y >= elem.end.y)
						cs2 = true;

				}
				if (cs1 && cs2) {
					pathmove = elem;

					return true;

				}

			}
		}

	return false;
}


////////////
void player::movepawn(int idd, sf::Vector2i cord)
{
			
			if (pathmove.opponentid>=0)
			player2->deletepawn(pathmove.opponentid);
			player_pawn[idd].moveforward(cord);
			if (std::abs(player_pawn[idd].struct_id().y - base) == 7)
				transform(idd);
	
	}
////////////////
void player::deletepawn(int x)
{
	int i;
	for (int f=0; f < PAWN_NUMBER; ++f) {
		if (player_pawn[f].struct_id().id == x)
			i = f;
	}
	player_pawn[i].dell();

}

pawns &player::pawn(int index)
{
	return player_pawn[index];
}

bool player::legalmove_id(int idd)
{
  if (!player_pawn[idd].path_pawn.empty())
  return true;
	
  return false;
}
bool player::checkfinish()
{
	for(int i=0;i<PAWN_NUMBER;++i)
	
	{
		if (legalmove_id(i))
			return false;

	}
	return true;
}
void player::lightpath(int idd)     
{
	possible_move = idd;
}


bool  player::return_path(sf::Vector2i cord)  //  mess
{

	if (possible_move < 0 || possible_move>11)
		return false;
		for (auto &elem : player_pawn[possible_move].path_pawn)
		{
			int xxx, yyy;
			xxx = elem.begin.x;
			yyy = elem.begin.y;
			int xx = 1;
			int yy = 1;
			if (elem.begin.x > elem.end.x)
				xx = -1;
			if (elem.begin.y > elem.end.y)
				yy = -1;

			while (xxx != elem.end.x && yyy != elem.end.y) {
				xxx = xxx + xx;
				yyy = yyy + yy;
				if (cord.x == xxx && cord.y == yyy) 
				{
					return true;
				}

			}
		}

	return false;
}


void player::transform(int index)
{
	player_pawn[index].king=true;
	player_pawn[index].transform();	
}

void player::erazemove(int index) {
	for (int i = 0; i < index + 1; ++i) 
	player_pawn[i].path_pawn.clear(); 
}
	
bool player::rightright(pawnmove array_pawnn,bool first_f )   
	{
	std::vector<int> nr = banned;
	pawnmove beginpath = array_pawnn;
	pawnmove cfour;
	int i;
	int holdid = -2;

	bool multi=false;
	bool first = first_f;
	bool save_move = first_f;
	bool eat=false;
	bool stagn = true;
	bool hold = false;
	
		
	for (int np = 0; np < PAWN_NUMBER * 8;++np)    // while (true)
	 {
	  i = auraright(array_pawnn);

	   if (i == -1) 
	   {

		if (hold == false && save_move == true) {

		  if (stagn == false) 
		  {

			if (eatormove)
				break;

		   player_pawn[indexxx].path_pawn.push_back(path{ beginpath,array_pawnn,holdid,beginpath,first,multi });

		   }

		}

		if (hold == true && save_move == true) 
       	player_pawn[indexxx].path_pawn.push_back(path{ beginpath,array_pawnn,holdid ,cfour,first,multi });

		break;
		}

		if (i == -2) 
		{
		 stagn = false;
		 increright(array_pawnn);	
		}

		if (i >= 0) 
		{

		 if (!eatormove)
		  {
			eatormove = true;
			erazemove(indexxx);
		  }

		   if (hold == true)
		    {
			  if (first == true)
				multi = true;

				player_pawn[indexxx].path_pawn.push_back(path{ beginpath,array_pawnn,holdid,EMPTY_PAWNMOVE,first,multi });
				beginpath = array_pawnn;
				first = false;
			}
	
					save_move = true;
					holdid = i;
					banned.push_back(i);
					cfour = array_pawnn;
					eatright(array_pawnn);

					eat = true;
					hold = true;

				}


				if (hold == true) {
					if (leftleft(array_pawnn, false) == true) {
						if (first == true)
							multi = true;
						player_pawn[indexxx].path_pawn.push_back(path{ beginpath,array_pawnn,holdid,EMPTY_PAWNMOVE,first,multi });
						save_move = false;
						

					}

					magic = magic * (-1);
					if (leftleft(array_pawnn, false) == true) {
						if (first == true)
							multi = true;
						save_move = false;

						player_pawn[indexxx].path_pawn.push_back(path{ beginpath,array_pawnn,holdid,EMPTY_PAWNMOVE,first,multi });
						
					}
					magic = magic * (-1);

				}
			
		}
		
		 banned = nr;
		return eat;
		}


bool player::leftleft(pawnmove array_pawnn, bool first_f )
{
	std::vector<int> nr = banned;
	
	
	pawnmove beginpath = array_pawnn;
	
	pawnmove cfour;
	int holdid = -2;

	int i;
	bool first = first_f;
	bool multi = false;
	bool stagn = true;
	bool eat = false;;
	bool hold = false;
	
	bool save_move = first;
	
	
	for (int np = 0; np < PAWN_NUMBER * 8; ++np)    // while (true)
	{

		i = auraleft(array_pawnn);
		if (i == -1) 
		{
			if (hold == false && save_move == true) {
				if (stagn == false) {
					if (eatormove)
						break;

					player_pawn[indexxx].path_pawn.push_back(path{ beginpath,array_pawnn,holdid,beginpath,first,multi });
				}
			}

			if (hold == true && save_move == true) 


				player_pawn[indexxx].path_pawn.push_back(path{ beginpath,array_pawnn,holdid,cfour,first,multi });

			
			break;
		}

		if (i == -2) 
		{
			stagn = false;
			
			increleft(array_pawnn);
		}
		if (i >= 0)
		{
			if (!eatormove)
			{
				eatormove = true;
				erazemove(indexxx);
			}
			if (hold == true) 
			{

				if (first == true)
					multi = true;
				player_pawn[indexxx].path_pawn.push_back(path{ beginpath,array_pawnn,holdid,EMPTY_PAWNMOVE,first,multi });
				beginpath = array_pawnn;
				first = false;
			}
			
				
			save_move = true;
			holdid = i;
			banned.push_back(i);
			cfour = array_pawnn;
			eatleft(array_pawnn);

			eat = true;
			hold = true;

		}
		if (hold == true) 
		{
			if (rightright(array_pawnn, false) == true) {
				if (first == true)
					multi = true;
				save_move = false;

				player_pawn[indexxx].path_pawn.push_back(path{ beginpath,array_pawnn,holdid,EMPTY_PAWNMOVE,first,multi });
			}



			magic = magic * (-1);
			if (rightright(array_pawnn, false) == true) {
				if (first == true)
					multi = true;
				save_move = false;

				player_pawn[indexxx].path_pawn.push_back(path{ beginpath,array_pawnn,holdid,EMPTY_PAWNMOVE,first,multi });

				
			}
			magic = magic * (-1);
			
		}

	}

		banned = nr;
		
		return eat;

}
	
		void player::increright(pawnmove &r)
		{
			r.x = r.x - magic;
			r.y = r.y + magic;
		}
		void player::increleft(pawnmove &r)
		{
			r.x = r.x + magic;
			r.y = r.y + magic;
		}
		void player::eatright(pawnmove &r)
		{
			increright(r);
			increright(r);
		}
		void player::eatleft(pawnmove &r)
		{
			increleft(r);
			increleft(r);
		}
	int player::auraright(pawnmove array_pawnn)
	{
		if (!borderright(array_pawnn))
			return -1;
		int i = emptyright(array_pawnn);
		if (i==-2)
			return -2;
		if (i == -1)
			return -1;
		if (i >= 0)
		{
			if (checkbanned(player2-> player_pawn[i].struct_id().id) == true)   
			return -2;
			if (emptyright(array_pawnn, magic) == -2 && borderright(array_pawnn, magic))
				return player2-> player_pawn[i].struct_id().id;
		
				return -1;
		}
		return -1;
	}
	int player::auraleft(pawnmove array_pawnn)
	{ 
		
		if (!borderleft(array_pawnn))
			return -1;
		int i = emptyleft(array_pawnn);
		if (i == -2)
			
			return -2;
		if (i == -1)
			return -1;
		if (i >= 0)
		{
			if (checkbanned(player2-> player_pawn[i].struct_id().id) == true)
			return -2;
		
			if (emptyleft(array_pawnn, magic) == -2 && borderleft(array_pawnn, magic))
				return player2-> player_pawn[i].struct_id().id;

			return -1;
		}
		return -1;
	}
	
	bool player::checkbanned(int i) {
		for (auto &elem : banned) {
			if (elem == i)
				return true; 
		}
		return false;
	}




	bool player::pawn_rightright(pawnmove array_pawnn, bool first )
	{
		bool multi=false;
		
		pawnmove beginpath = array_pawnn;
		
		int i;
		bool b1, b2;
		bool eat = false;
		int holdid = -2;
		
		
			i = auraright(array_pawnn);
			if (i == -2) {
				if (!eatormove)
				{
					increright(array_pawnn);
					player_pawn[indexxx].path_pawn.push_back(path{ beginpath,array_pawnn,holdid,EMPTY_PAWNMOVE,first,multi });
				}
				}
			
			if (i >= 0) {
				if (!eatormove)
				{
					eatormove = true;
					erazemove(indexxx);
				}
				holdid = i;
				eat = true;
				
				eatright(array_pawnn);
				
			
				b1 = pawn_leftleft(array_pawnn, false);
				b2 = pawn_rightright(array_pawnn, false);
					multi = b1 || b2;
				
				player_pawn[indexxx].path_pawn.push_back(path{ beginpath,array_pawnn,holdid,EMPTY_PAWNMOVE,first,multi });
			}
			

		return eat;
	}

	bool player::pawn_leftleft(pawnmove array_pawnn, bool first )
	{
		bool multi=false;
		
		pawnmove beginpath = array_pawnn;

		int i;
		bool b1, b2;
		bool eat = false;
		int holdid = -2;
		

		i = auraleft(array_pawnn);
		if (i == -2) {

			if (!eatormove)
			{

				increleft(array_pawnn);
				player_pawn[indexxx].path_pawn.push_back(path{ beginpath,array_pawnn,holdid,EMPTY_PAWNMOVE,first,multi });
			}
		}

		if (i >= 0) {
			if (!eatormove)
			{
				eatormove = true;
				erazemove(indexxx);
			}
			holdid = i;
			eat = true;
			eatleft(array_pawnn);
			
			b1 = pawn_rightright(array_pawnn, false);
			b2 = pawn_leftleft(array_pawnn, false);
				multi = b1 || b2 ;
			player_pawn[indexxx].path_pawn.push_back(path{ beginpath,array_pawnn,holdid,EMPTY_PAWNMOVE,first,multi });


		}


		return eat;
	}

/*
void player::symmetry()
{
	for (int i = 0; i < PAWN_NUMBER; ++i)
	{
		array_pawn[i].x = std::abs(array_pawn[i].x - 7);
		array_pawn[i].y = std::abs(array_pawn[i].y - 7);
		player2->array_pawn[i].x = std::abs(player2->array_pawn[i].x - 7);
		player2->array_pawn[i].y = std::abs(player2->array_pawn[i].y - 7);
		player_pawn[i].symmetry();
		player2->player_pawn[i].symmetry();
	}
} 
*/