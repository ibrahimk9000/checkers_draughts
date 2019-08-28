
#include "game.h"
//  board square  100x100  coordinate in window 800x800
// pawn circle 50 diameter
//board and pawns coordinate in window 
const float G_xcord[8] = { 0.0f,100.0f,200.0f,300.0f,400.0f,500.0f,600.0f,700.0f };
const float G_ycord[8] = { 0.0f,100.0f,200.f,300.0f,400.0f,500.0f,600.0f,700.0f };

Game::Game():window(sf::VideoMode(800, 800), "Checkers", sf::Style::Close) {};

void Game::boardinit()
{
	for (int i = 0; i < 32; ++i) 
	{
		//initialise vector of 32 board black and white 

		boardwhite.push_back(board(0,i));  
	                                 //param 0 and  for positioning 
		boardblack.push_back(board(1,i));
	}
}


void Game::playerinit()
{
	playertwo = player(PLAYER_TWO);
	playerone = player(PLAYER_ONE);
}
void Game::endblackrectangle() {
	finish = sf::RectangleShape(sf::Vector2f(800, 800));
	finish.setFillColor(sf::Color(0, 0, 0, 40));
}

bool Game::initfont() {
	if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"))
	{

		return true;
	}

	txt.setFont(font);

	txt.setCharacterSize(40);
	txt.setFillColor(sf::Color::White);
	txt.setPosition(275.0, 375.0);

}
bool Game::run() {
	bool stat= false;

	window.setFramerateLimit(40);
	boardinit();
	playerinit();
	endblackrectangle();
	Game::initfont();
 
 stat=Game::events();
 return stat;

}
void Game::draw()
{

	window.clear();

	for (auto i = 0; i < 32; ++i)
	{
		window.draw(boardwhite[i].display());   // draw board case

		window.draw(boardblack[i].display());
		if (turn().return_path(boardblack[i].cord()))
			window.draw(boardblack[i].display_path());   //draw pawn move possbilities
	}
	for (int i = 0; i < PAWN_NUMBER; ++i)
	{
		if (notmyturn().pawn(i).get_id() != 12)
			window.draw(notmyturn().pawn(i).display());
	}
	for (int i = 0; i < PAWN_NUMBER; ++i)
	{
		if (turn().pawn(i).get_id() != 12)
			window.draw(turn().pawn(i).display());   //draw pawn texture

		if (turn().legalmove_id(i))
			window.draw(turn().pawn(i).displayborder());   // draw texture of pawn that can be moved
	
		if (turn().checkfinish()) {
			window.draw(finish);
			if (turn().getplayer_id() == 5)
			
				txt.setString("Playerone Win");
			else 
				txt.setString("Playertwo Win");

			window.draw(txt);
		}
		

	}


 window.display();
}

bool Game::events()
{
 bool clicked = false;  // for mouse move
 int indexx;
 sf::Event event;

 playerone.enable(true);  
 turn().status(&notmyturn());  //check status of player pawn if can be moved or can eat

 while (window.isOpen())
 {

  Game::draw();

  while (window.pollEvent(event))
  {
   
   switch (event.type) 
   {

    case sf::Event::MouseButtonPressed:
	  if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
		  if (turn().checkfinish())
			  return false;
		 if (clicked == false)   // to prevent trigger mousebuttonpressed event  when mouse button realised
		  {
		    for (int i = 0; i < PAWN_NUMBER; ++i) 
			 {
			// define the pawn selected by mouse
			  if (turn().pawn(i).display().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) 
			  { 
				clicked = true;
				indexx = i;
				turn().lightpath(turn().pawn(i).get_id());  //reveal the possible move of the pawn selectd
				turn().pawn(i).select(event.mouseButton.x, event.mouseButton.y);  //store the mouse position when select pawn
				break;
			  }
			}
		  }
		}
	break;

	case sf::Event::MouseMoved:
	 if (event.type == sf::Event::MouseMoved && clicked == true)
		//move the pawn when mouse moved ( drop and down )
		if (turn().legalmove_id(indexx))
		turn().pawn(indexx).move(event.mouseMove.x, event.mouseMove.y);
	break;

	case sf::Event::MouseButtonReleased:
     if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && clicked == true )
	  {
	   for (int i = 0; i < 32; ++i)
	    {
		//define the board case that pawn moved to  and check if possible to move  to it
		 if (boardblack[i].display().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && turn().movelegal(indexx, boardblack[i].cord()))
		  {
		    turn().movepawn(indexx, boardblack[i].cord());
			//disable selected pawn possible move texture
			turn().lightpath(12);
			if (turn().multieatt()<0)
			 swap();   //swap to oppoent player

			turn().status(&notmyturn());
			clicked = false;
			break;
		  }
		}

	  if (clicked == true)
	   {
		//reset move if move is not legal
		turn().pawn(indexx).resetmove();
		clicked = false;
	   }
	 }
	break;
   }
  }
  if (event.type == sf::Event::Closed) {
  window.close();
   
	return true;
  }

 }
}

	// return player who can have the turn
player &Game::turn() {  
	if (playerone.enabled() == true)
		return playerone;
	return playertwo;
}
player &Game::notmyturn() {
	if (playerone.enabled() == false)
		return playerone;
	return playertwo;
}
void Game::swap() // swap  between playerone and playertwo
{
	if (playerone.enabled()==false)
	{
		playerone.enable(true);
		playertwo.enable(false);
	}
	else
	{
		playerone.enable(false);
		playertwo.enable(true);
	}
}