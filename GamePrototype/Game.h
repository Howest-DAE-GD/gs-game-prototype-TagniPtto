#pragma once
#include "BaseGame.h"

#include <list>
#include <vector>
class TextureManager;
class Player;
class Level;
class Oven;
class Pizza;
class Projectile;
typedef void (*ShootingFunction)(Projectile* prjc, std::list<Projectile*>& projectileList, Player* parent);

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

	Oven* g_pOven1{nullptr};
	Player* g_pPlayer{ nullptr };
	Level* g_pLevel{nullptr};
	std::vector<Projectile*>g_ProjectileSamples;
	std::vector<ShootingFunction>g_shootingFunctionLibrary;

	TextureManager* g_pTextureManager{nullptr};
private:
	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};