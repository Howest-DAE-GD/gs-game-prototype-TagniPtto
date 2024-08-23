#pragma once
#include "BaseGame.h"

#include <list>

class AnimationManager;
class Player;
class Texture;

class Projectile;
class Enemy;

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

	std::list<Projectile*> g_projectiles;
	std::list<Enemy*> g_enemies;
	Player* g_pPlayer{nullptr};
	Texture* g_pBackground{nullptr};
	Texture* g_pCrosshair{nullptr};

private:
	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};