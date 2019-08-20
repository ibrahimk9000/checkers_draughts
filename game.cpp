
#define PLAYER_ONE 0
#define PLAYER_TWO 5
#define PAWN_NUMBER 12
#include "game.h"
//  board square  100x100  coordinate in window 800x800
// pawn circle 50 diameter
//board and pawns coordinate in window 
const float G_xcord[8] = { 0.0f,100.0f,200.0f,300.0f,400.0f,500.0f,600.0f,700.0f };
const float G_ycord[8] = { 0.0f,100.0f,200.f,300.0f,400.0f,500.0f,600.0f,700.0f };

Game::Game():window(sf::VideoMode(800, 800), "Checkers") {};

void Game::run() {
	window.setFramerateLimit(40);
#ifdef _WIN32
texture tex("d:\\classic-piece-black.png");    // load texture
texture tex1("d:\\classic-square-white.png");
texture tex4("d:\\borderr.png");
texture tex5("d:\\vector-frame-png-transparent-images-150122-33546554.png");
texture tex2("d:\\fire.png");
texture tex3("d:\\blue.png");
texture tex6("d:\\fire_king.png");
texture tex7("d:\\blue_king.png");
#endif
#ifdef __linux__
texture tex("/home/ibrahim/checker/classic-piece-black.png");    // load texture
texture tex1("/home/ibrahim/checker/classic-square-white.png");
texture tex4("/home/ibrahim/checker/borderr.png");
texture tex5("/home/ibrahim/checker/vector-frame-png-transparent-images-150122-33546554.png");
texture tex2("/home/ibrahim/checker/fire.png");
texture tex3("/home/ibrahim/checker/blue.png");
texture tex6("d:\\fire_king.png");
texture tex7("d:\\blue_king.png");
#endif
for (int i = 0; i < 32; ++i) {
	//initialise vector of 32 board black and white 
	boardwhite.push_back(board(0, tex1.map(),nullptr));    //param 0 and  for positioning 
	boardblack.push_back(board(1, tex.map(),tex5.map()));
}



//inistialise players  
playertwo = player(PLAYER_TWO, tex3.map(), tex4.map());
 playerone=player(PLAYER_ONE, tex2.map(),tex4.map());
 

 Game::events();
 
 
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
 if (turn().pawn(i).get_id() != 12)
 window.draw(turn().pawn(i).display());   //draw pawn texture

  if (notmyturn().pawn(i).get_id() != 12)
  window.draw(notmyturn().pawn(i).display());

  if (turn().legalmove_id(i))
   window.draw(turn().pawn(i).displayborder());   // draw texture of pawn that can be moved

}

 window.display();
}

void Game::events()
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
  if (event.type == sf::Event::Closed)
				window.close();
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