#pragma once

#include "Entity.h"
#include "Texture.h"


#include "InputBuffer.h"
#include "AnimationManager.h"
#include "SfxManager.h"

#include <list>

class Projectile;


class Player : public Entity
{
	enum class ProjectileType {
		none,
		Bread,
		Cake,
		Pizza,
	};
public:


	Player(Vector2f position = {}, Vector2f velocity = {});
	~Player();
	void Update(float elapsedSec) override;
	void Draw() const override;
	void HandleKeyBoardInput(float elapsedSec);
	void HandleMouseInput(const Point2f mousePos);

	void Shoot(std::list<Projectile*>& projectiles);
	void Toggle();


	bool isInvincible{false};
private:

	const float MaxMovementSpeed{ 500 };
	const float acceleration{ 0.3f };
	float m_elapsedSec{};

	Vector2f directionVector;
	AnimationManager m_pAnimationManager_MuzzleFlash;
	AnimationManager m_pAnimationManager_Explosion;
	SfxManager m_pSfxManager;

	InputBuffer m_pInputBuffer;
	Texture* m_pTexture;
};

