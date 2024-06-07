#include "pch.h"
#include "Game.h"
#include "iostream"



Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}



void Game::Initialize( )
{
	std::cout << "----   HOW TO PLAY   ----" << "\n";
	std::cout << "Arrow keys to move"<<"\n";
	std::cout << "Reach the white square to win" << "\n";
	std::cout << "Enemies can go through walls" << "\n";
	
	Point2f pos(rand() % 300, rand() %100 + 600);
	player = new Player(pos);
	
	for (int i = 0; i < 3; ++i)
	{
		Point2f epos(rand() % 300 + 300*(i+1), rand() % 150 + 200*(i+1));
		enemy[i] = new Enemy(epos);
	}
	
	exit = new Point2f(Point2f(rand() % 300 + 850, rand() % 300));
	
	
	
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{

	for (int i = 0; i < 3; ++i)
	{
		player->hitcheck(enemy[i]->hitcheck());
	}

	for (int i = 0; i < 3; ++i)
	{
		enemy[i]->chase(player->chase());
	}

	player->mapbounds();
	
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	if ( pStates[SDL_SCANCODE_RIGHT] )
	{
		player->Right();
	}
	if (pStates[SDL_SCANCODE_LEFT])
	{
		player->Left();
	}
	if (pStates[SDL_SCANCODE_UP])
	{
		player->Up();
	}
	if (pStates[SDL_SCANCODE_DOWN])
	{
		player->Down();
	}
}

void Game::Draw( ) const
{
	ClearBackground( );
	
	if (player->gamestate())
	{
		player->Draw();
		for (int i = 0; i < 3; ++i)
		{
			enemy[i]->Draw();
		}


		player->drawmap();
		player->healthbar();
		player->exit(exit);
	}
	
	
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
