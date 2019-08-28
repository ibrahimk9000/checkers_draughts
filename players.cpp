#include "players.h"

player::player(int plyr) :player_id(plyr) 
{
	  //initialise vector of pawns
		
		if (player_id == 5)
		{
			for (int i = 11; i >=0 ; --i)
				player_pawn.push_back(pawns(player_id,i));

			base = 7;
		}
		else {
			for (int i = 0; i < PAWN_NUMBER; ++i)
			player_pawn.push_back(pawns(player_id,i));

			base = 0;
		}

	
}

player::player() {};

int player::getplayer_id()

{
	return player_id;
}
void player::status(player* opp)
{
	//clear past data
	
	player2 = opp; //pointer to opponent player
	eatormove = false;
	
	erazemove(11);
	if (player2->getplayer_id() == 0)   //player two start from position 7 and player one stat form position 0
		magic = -1;
	else
		magic = 1;
	//symmetry();
	for (int i = 0; i < PAWN_NUMBER; ++i)
	{
		if (multieat > 0 && multieat != i)
			continue;
		if ( player_pawn[i].struct_id().id < 12)
		{
			indexxx = i;
			if (player_pawn[i].kings() == true)
			{
				rightright( player_pawn[i].struct_id(), true, 0);
				leftleft( player_pawn[i].struct_id(), true, 0);
				magic = magic * (-1);

				rightright( player_pawn[i].struct_id(), true, 0);
				leftleft( player_pawn[i].struct_id(), true, 0);
				magic = magic * (-1);

			}
			else {
			//check pawns statis right and left path possibilities
				rightright( player_pawn[i].struct_id(), false, 0);
				leftleft( player_pawn[i].struct_id(), false, 0);
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
	for (auto &elem : player_pawn[idd].path_pawnn) {
		if (elem.first == false)
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
		
	
		begin = elem.begin;
		end = elem.end;
		if (elem.opponentid >= 0)
			mag = 1;
		
		x = begin.x-end.x;
		
		y = begin.y - end.y;
		if (elem.eatstatus.id==-2){
			if (coor.x == elem.end.x && coor.y == elem.end.y)
			{
				pathmove = elem;
				multieat = idd;
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


int player::multieatt()
{
	return multieat;
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
	for (int f=0; f < 12; ++f) {
		if (player_pawn[f].get_id() == x)
			i = f;
	}
	
				player_pawn[i].dell();
			
}
void player::enable(bool status)
{
	active_status = status;
}
bool player::enabled()
{
	return active_status;
}
pawns &player::pawn(int index)
{
	return player_pawn[index];
}
std::vector<pawns> &player::vect_pawn()
{
	return player_pawn;
}

bool player::legalmove_id(int idd)
{
  if (!player_pawn[idd].path_pawnn.empty())
  return true;
	
  return false;

}
bool player::checkfinish()
{
	for (int i = 0; i < 12; ++i)
	{
		if (legalmove_id(i))
			return false;
	}
	return true;
}
void player::lightpath(int idd)
{
	path_move = idd;
}
bool  player::return_path(sf::Vector2i cord)
{
	for (int i = 0; i < 12; ++i) {
		for (auto &elem : player_pawn[i].path_pawnn)
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
				if (cord.x == xxx && cord.y == yyy && elem.begin.id == path_move)
				{
					return true;
					//	break;
				}

			}
		}
	}
	return false;
}


void player::transform(int index)
{
	//change texture
	player_pawn[index].setking(true);
	player_pawn[index].transform();
	
}

void player::erazemove(int index) {
	for (int i = 0; i < index + 1; ++i) {
		player_pawn[i].path_pawn(path{ beginpath,beginpath,20,{0,0,0},false });

}
}
	
bool player::rightright(pawnmove array_pawnn, bool bflag,int flag = 0)
	{
	bool bannedd;
		pawnmove beginpath = array_pawnn;
		pawnmove begg = array_pawnn;
		pawnmove cfour;
		int i;
		bool eat=false;
		bool stagn = true;
		bool hold = false;
		int holdid=-2;
		bool j = true;
		bool iter = true;
		int flagg = flag;
		if (flag == 0)
			bannedd = false;
		else
			bannedd = true;
		
		while (true)
		{


			i = auraright(array_pawnn);
			if (i == -1) {
				if (hold == false && flag == 0) {
					if (stagn == false) {
						if (eatormove)
							break;
				
						player_pawn[indexxx].path_pawn(path{ beginpath,array_pawnn,-2,beginpath,bannedd });
					}

				}

				if (hold == true && flag == 0) {
					if (bflag == true) {
						
						player_pawn[indexxx].path_pawn(path{ beginpath,array_pawnn,holdid ,cfour,bannedd });
					}
					else {
					
						player_pawn[indexxx].path_pawn(path{ beginpath,array_pawnn,holdid,cfour,bannedd });
					}
			}
				break;
			}
			if (i == -2) {
				stagn = false;
				if (bflag == false && hold == true) {
					player_pawn[indexxx].path_pawn(path{ beginpath,array_pawnn,holdid,cfour,bannedd });
					break;
				}
				increright(array_pawnn);
				if (bflag == false)
				{ 
					if (eatormove)
						break;
					
					player_pawn[indexxx].path_pawn(path{ beginpath,array_pawnn,-2,beginpath,bannedd });
					break;
				}
				//if (hold==true)


			}
			if (i >= 0) {
				if (!eatormove)
				{
					eatormove = true;
					erazemove(indexxx);
				}
				if (hold == true)
				{
					player_pawn[indexxx].path_pawn(path{ beginpath,array_pawnn,holdid,{-2+bannedd,0,0},bannedd });
					beginpath = array_pawnn;
					bannedd = true;
				}
				flag = 0;
				holdid = i;
				banned.push_back(i);
				cfour = array_pawnn;
				eatright(array_pawnn, i);
				
				eat = true;
				hold = true;
				
			}
			if (hold == true) {
				if (leftleft(array_pawnn,bflag, 1) == true) {
					
					player_pawn[indexxx].path_pawn(path{ beginpath,array_pawnn,holdid,{-2+bannedd,0,0},bannedd });
					flag = 1;
				}
				if (bflag == false) {
				
				//	player_pawn[indexxx].path_pawn(path{ beginpath,array_pawnn,holdid,2 });
				//	break;
				}
				if (bflag == true) {
					magic = magic * (-1);
					if (leftleft(array_pawnn,bflag, 1) == true) {

						flag = 1;
						
						player_pawn[indexxx].path_pawn(path{ beginpath,array_pawnn,holdid,{-2+bannedd,0,0},bannedd });
					}
					magic = magic * (-1);
					
				}
				if (flagg == false)
					banned.clear();
				
			}
			//flag = 1;
			
		}
		
		return eat;
		}


	bool player::leftleft(pawnmove array_pawnn,bool bflag, int flag = 0)
	{
		bool bannedd;
		pawnmove beginpath = array_pawnn;
		pawnmove begg = array_pawnn;
		pawnmove cfour;
		int i;
		bool stagn = true;
		bool eat = false;;
		bool hold = false;
		int holdid = -2;
		bool j = true;
		bool iter = true;
		int flagg = flag;
		if (flag == 0)
			bannedd = false;
		else
			bannedd = true;
		while (true)
		{

			i = auraleft(array_pawnn);
			if (i == -1) {
				if (hold == false && flag == 0) {
					if (stagn == false) {
						if (eatormove)
							break;
					
						player_pawn[indexxx].path_pawn(path{ beginpath,array_pawnn,-2,beginpath,bannedd });
				}
				}

				if (hold == true && flag == 0) {
					if (bflag == true) {
						
						player_pawn[indexxx].path_pawn(path{ beginpath,array_pawnn,holdid,cfour,bannedd });
					}
					else {
						
						player_pawn[indexxx].path_pawn(path{ beginpath,array_pawnn,holdid,cfour,bannedd });
					}
				}
				break;
			}
			if (i == -2) {
				stagn = false;
				if (bflag == false && hold == true) {
					player_pawn[indexxx].path_pawn(path{ beginpath,array_pawnn,holdid,cfour,bannedd });
					break;
				}
				increleft(array_pawnn);
				if (bflag == false)
				{
					if (eatormove)
						break;
					
					player_pawn[indexxx].path_pawn(path{ beginpath,array_pawnn,-2,beginpath,bannedd });
					break;
				}
				//if (hold==true)

			}
			if (i >= 0) 
			{
				if (!eatormove)
				{
					eatormove = true;
					erazemove(indexxx);
				}
				if (hold == true) {
				
					
					player_pawn[indexxx].path_pawn(path{ beginpath,array_pawnn,holdid,{-2+bannedd,0,0 },bannedd });
					beginpath = array_pawnn;
					bannedd = true;
				}
				flag = 0;
				holdid = i;
				banned.push_back(i);
				cfour = array_pawnn;
				eatleft(array_pawnn, i);
				
				eat = true;
				hold = true;

			}
			if (hold == true) {
				if (rightright(array_pawnn,bflag, 1) == true) {

					flag = 1;
					
					player_pawn[indexxx].path_pawn(path{ beginpath,array_pawnn,holdid,{-2+bannedd,0,0 },bannedd });
				}
				if (bflag == false) {
					
				//	player_pawn[indexxx].path_pawn(path{ beginpath,array_pawnn,holdid,2 });
				//	break;
				}
				if (bflag == true) {
					magic = magic * (-1);
					if (rightright(array_pawnn,bflag, 1) == true) {

						flag = 1;
						
						player_pawn[indexxx].path_pawn(path{ beginpath,array_pawnn,holdid,{-2+bannedd,0,0 },bannedd });
					}
					magic = magic * (-1);
				}
				if (flagg == false)
					banned.clear();
			}
			//flag = 1;

		}
		
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
		bool player::eatright(pawnmove &r, int i)
		{
		
			increright(r);
			increright(r);
			return false;
			
		}
		bool player::eatleft(pawnmove &r, int i)
		{

			increleft(r);
			increleft(r);
			return false;

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



/*
void player::symmetry()
{
	for (int i = 0; i < 12; ++i)
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