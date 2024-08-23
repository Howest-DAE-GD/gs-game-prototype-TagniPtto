#include "pch.h"
#include "Game.h"
#include "iostream"
#include "string"

#include "utils.h"


#include "Player.h"
#include "Projectile.h"
#include "Texture.h"
#include "Enemy.h";


static float mouseX , mouseY;
float timer;
const float SpawnDuration{7.5f};
int score{0};
bool GameIsRunning{ true };

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
}
void Game::Initialize( )
{
	std::srand(std::time(nullptr));
	g_pPlayer = new Player(Vector2f{ GetViewPort().width / 2.f ,GetViewPort().height / 2.f });
	Enemy::g_basicEnemySpriteSheet = new Texture("EnemySpriteSheet1.png");
	Enemy::g_Target = g_pPlayer;
	g_pBackground = new Texture("Background.jpg");
	g_pCrosshair = new Texture("CrossHair.png");

}

void Game::Cleanup( )
{
	delete g_pBackground;
	delete g_pCrosshair;
	delete Projectile::g_pBasicProjectileTexture;
	for (Projectile*& p : g_projectiles) {
		delete p;
		p = nullptr;
	}
	for (Enemy*& e : g_enemies) {
		delete e;
		e = nullptr;
	}

	g_pBackground = nullptr;
	Projectile::g_pBasicProjectileTexture = nullptr;
}

void Game::Update(float elapsedSec)
{
	if (!GameIsRunning) {
		return;
	}
	if (g_pPlayer->GetHealth() <= 0) {
		GameIsRunning = false;
	}
	timer += elapsedSec;
	if (timer > 2.0f) {
		timer = 0;
		int dir{std::rand()%4};
		switch (dir)
		{
		case 0:
			g_enemies.push_back(new Enemy(Vector2f{ float(std::rand() % int(GetViewPort().width)),0 }));
			break;
		case 1:
			g_enemies.push_back(new Enemy(Vector2f{ 0,float(std::rand() % int(GetViewPort().height)) }));
			break;
		case 2:
			g_enemies.push_back(new Enemy(Vector2f{ float(std::rand() % int(GetViewPort().width)),GetViewPort().height }));
			break;
		case 3:
			g_enemies.push_back(new Enemy(Vector2f{GetViewPort().width,float(std::rand() % int(GetViewPort().height)) }));
			break;
		default:
			break;
		}
		
	}

	g_pPlayer->Update(elapsedSec);
	if (g_pPlayer->GetPosition().x < 0 or g_pPlayer->GetPosition().x > GetViewPort().width) {
		g_pPlayer->SetVelocity(Vector2f{ -g_pPlayer->GetVelocity().x,g_pPlayer->GetVelocity().y });
	}
	if (g_pPlayer->GetPosition().y < 0 or g_pPlayer->GetPosition().y > GetViewPort().height) {
		g_pPlayer->SetVelocity(Vector2f{ g_pPlayer->GetVelocity().x,-g_pPlayer->GetVelocity().y });
	}
	g_pPlayer->SetPosition(Vector2f{
		utils::Clamp(0, GetViewPort().width, g_pPlayer->GetPosition().x),
		utils::Clamp(0, GetViewPort().height, g_pPlayer->GetPosition().y)
		});


	for (Projectile*& p : g_projectiles) {
		if (p != nullptr) {
			p->Update(elapsedSec, g_enemies);
		}
	}
	for (Enemy*& p : g_enemies) {
		if (p != nullptr) {
			p->Update(elapsedSec);
		}
	}
	for (auto itr = g_projectiles.begin();
		itr != g_projectiles.end();) {
		if (((*itr)->GetPosition().x < 0 or (*itr)->GetPosition().x > GetViewPort().width) or
			((*itr)->GetPosition().y < 0 or (*itr)->GetPosition().y > GetViewPort().height)) {
			delete (*itr);
			(*itr) = nullptr;
			itr = g_projectiles.erase(itr);
		}else {
			++itr;
		}
	}
	for (auto itr = g_enemies.begin();
		itr != g_enemies.end();) {
		if ((*itr)->GetHealth() <= 0) {
			delete (*itr);
			(*itr) = nullptr;
			itr = g_enemies.erase(itr);
			score += 100;
		}
		else {
			++itr;
		}
	}
	
	
}

void Game::Draw( ) const
{
	float width{ 50 }, height{ 50 };
	Rectf dst{ -width / 2.f,-height / 2.f ,width,height };
	ClearBackground( );// Rectf{ 0,0,GetViewPort().width,GetViewPort().height }
	glPushMatrix(); {
		const float bkgScale{0.45f};
		glScalef(bkgScale, bkgScale,1.0f);
		g_pBackground->Draw();
	}
	glPopMatrix();
	glPushMatrix(); {
		const float chScale{ 0.5f };
		glTranslatef(mouseX, mouseY, 0.f);
		glScalef(chScale, chScale, 1.0f);
		g_pCrosshair->Draw(dst);
	}
	glPopMatrix();

	g_pPlayer->Draw();
	for (Projectile* p : g_projectiles) {
		p->Draw();
	}
	for (Enemy* e : g_enemies) {
		e->Draw();
	}
	std::string result{ std::to_string(score) };
	Texture score(result, std::string("Nasa21.ttf"), 30, Color4f{0.2f,1.0f,0.1f,1.0f});
	dst = Rectf{ 60,GetViewPort().height-50,30,50};
	score.Draw(dst);

	Texture EndScreen("DEFEATED Press 0 to restart", std::string("Nasa21.ttf"), 20, Color4f{0.2f,1.0f,0.1f,1.0f});
	dst = Rectf{ 0,100,700,100 };
	if (!GameIsRunning) {
		EndScreen.Draw(dst);
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{

	if (!GameIsRunning) {
		if (e.keysym.sym == SDLK_0)
		{
			score = 0;
			GameIsRunning = true;
			g_pPlayer->SetHealth(10);
			for (Enemy*& e : g_enemies) {
				delete e;
				e = nullptr;
			}
			for (Projectile*& e : g_projectiles) {
				delete e;
				e = nullptr;
			}
			g_enemies.clear();
			g_projectiles.clear();

		}
	}

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
	mouseX = float(e.x);
	mouseY = float(e.y);
	g_pPlayer->HandleMouseInput(Point2f{ mouseX,mouseY });
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{

	
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		g_pPlayer->Shoot(g_projectiles);
		break;
	case SDL_BUTTON_RIGHT:
		break;
	case SDL_BUTTON_MIDDLE:
		std::cout << " middle button " << std::endl;
		break;
	default:
	
		break;
	}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{

}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
