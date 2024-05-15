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
	std::cout << "Imposter +  consumption" << std::endl;
	std::string mapVertsPath("Map2.svg");
	std::string mapTexturePath("");
	m_pLevel = new Level(mapVertsPath,mapTexturePath);
	m_pCamera = new Camera(GetViewPort().width, GetViewPort().height, Point2f{ GetViewPort().width/2.f, GetViewPort().height /2.f});
	m_pPlayer = new Player();


}

void Game::Cleanup( )
{
	delete m_pLevel;
	delete m_pCamera;
	delete m_pPlayer;
	m_pLevel = nullptr;
	m_pCamera = nullptr;
	m_pPlayer = nullptr;

}

void Game::Update(float elapsedSec)
{
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
	//m_pCamera->Update(elapsedSec);
	m_pPlayer->Update(elapsedSec);
	m_pLevel->Update(elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground( );
	m_pCamera->Aim(m_pLevel->GetBorder(), m_pPlayer->GetPosition()); {
		m_pCamera->ApplyTransformation();
		utils::SetColor(Color4f{1.f,1.f,1.f,1.f});
		//utils::FillRect(Rectf{ GetViewPort().width/2.f, GetViewPort().height / 2.f, 10.f,10.f} );
		m_pLevel->Draw();
		m_pPlayer->Draw();
	}m_pCamera->Reset();

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
	m_pPlayer->LookAt(Vector2f{float(e.x +m_pCamera->GetPosition().x - GetViewPort().width/2.f),
		float( e.y + m_pCamera->GetPosition().y - GetViewPort().height / 2.f)});
	// global mouseCoordinate = mouseposition + camera position - viewportwidth/2
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
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
