#include "pch.h"
#include <iostream>
#include <list>

#include "utils.h"

#include "Player.h"

#include "Projectile.h"

Player::Player(Vector2f position, Vector2f velocity) :
	Entity::Entity(position, velocity),
	m_pTexture(new Texture("Oven.png")),
	m_pInputBuffer(5),
	m_pSfxManager(),
	m_pAnimationManager_Explosion("CartoonExplosion.png"),
	m_pAnimationManager_MuzzleFlash("MuzzleFlash.png")
{

	m_pSfxManager.AddSfx("sfx/OvenDoor.mp3","NormalShot");
	m_pSfxManager.AddSfx("sfx/BowRelease.mp3","NormalShot2");

	m_pAnimationManager_Explosion.AddAnimation("main", Point2f{ 0,0 },
		m_pAnimationManager_Explosion.GetSpriteSheetWidth() / 6.f,
		m_pAnimationManager_Explosion.GetSpriteSheetHeight(), 6, 0.03f, Animation::AnimationMode::normal);
	m_pAnimationManager_MuzzleFlash.AddAnimation("main", Point2f{ 0,0 },
		m_pAnimationManager_MuzzleFlash.GetSpriteSheetWidth() / 4.f,
		m_pAnimationManager_MuzzleFlash.GetSpriteSheetHeight(), 4, 0.05f, Animation::AnimationMode::normal);
	
}
Player::~Player()
{
	delete m_pTexture;
}
void Player::Update(float elapsedSec)
{

	m_pInputBuffer.Update(elapsedSec);
	HandleKeyBoardInput(elapsedSec);
	m_pAnimationManager_MuzzleFlash.Update(elapsedSec);
	m_pAnimationManager_Explosion.Update(elapsedSec);
	Entity::Update(elapsedSec);

	m_Velocity.x = utils::Clamp(-MaxMovementSpeed, MaxMovementSpeed, m_Velocity.x);
	m_Velocity.y = utils::Clamp(-MaxMovementSpeed, MaxMovementSpeed, m_Velocity.y);

}

void Player::Draw() const
{
	utils::SetColor(Color4f{1.0f,0.2f,0.1f,1.0f});
	utils::DrawLine(m_Position.ToPoint2f(), (m_Position + m_DirectionVector).ToPoint2f() , 1.0f);


	float width{ 50 }, height{ 50 };
	Rectf dst{ -width / 2.f,-height / 2.f ,width,height };


	glPushMatrix(); {

		glTranslatef(m_Position.x, m_Position.y, 0.f);
		glRotatef(m_angle ,0.f,0.f,1.f);
		m_pTexture->Draw(dst);

		float muzzleFlash_size{ 30 };
		glTranslatef(0, muzzleFlash_size + 10, 0);
		glRotatef(90 ,0.f,0.f,1.f);
		if (!m_pAnimationManager_MuzzleFlash.GetCurrentAnimation().m_EofAnimation) {
			m_pAnimationManager_MuzzleFlash.Draw(Rectf{ -muzzleFlash_size,-muzzleFlash_size,2 * muzzleFlash_size,2 * muzzleFlash_size });
		}
	}glPopMatrix();

}

void Player::HandleKeyBoardInput(float elapsedSec)
{

	//std::cout << "angle: " << m_angle << std::endl;

	if (int((m_pInputBuffer)[0]) & int(Input::ARROW_DOWN)) {
		m_Velocity.y -= MaxMovementSpeed * acceleration * elapsedSec;
	}
	if (int((m_pInputBuffer)[0]) & int(Input::ARROW_UP)) {
		m_Velocity.y += MaxMovementSpeed * acceleration * elapsedSec;
	}
	if (int((m_pInputBuffer)[0]) & int(Input::ARROW_LEFT)) {
		m_Velocity.x -= MaxMovementSpeed * acceleration * elapsedSec;
	}
	if (int((m_pInputBuffer)[0]) & int(Input::ARROW_RIGHT)) {
		m_Velocity.x += MaxMovementSpeed * acceleration * elapsedSec;
	}

	if (int((m_pInputBuffer)[0]) == int(Input::EMPTY)) {
		m_Velocity *= 0.99f;
	}


}

void Player::HandleMouseInput(const Point2f mousePos)
{
	directionVector = Vector2f{ m_Position.ToPoint2f() , mousePos };
	//std::cout << "directionVector: " << directionVector  << std::endl;
	m_angle = -directionVector.AngleWith(Vector2f{ 1.0f,0.0f }) * 180.f / 3.14f - 90;

}

void Player::Shoot(std::list<Projectile*>& projectiles)
{
	m_pAnimationManager_MuzzleFlash.SetAnimation("main");
	m_pSfxManager.Play("NormalShot");
	float ProjectileSpeed{ 500 };
	float knockBackPercentage{ 0.2f };
	Projectile* p{ new Projectile(m_Position, Vector2f{cos((m_angle + 90) * 3.14f / 180.f),sin((m_angle + 90) * 3.14f / 180.f)} *ProjectileSpeed,m_angle + 90,this) };
	
	const float maxAngVel{200};
	const float minAngVel{20};

	
	p->SetAngularVelocity(std::rand()%int(maxAngVel- minAngVel) + minAngVel);
	projectiles.push_back(p);
	m_Velocity -= Vector2f{ cos((m_angle + 90) * 3.14f / 180.f), sin((m_angle + 90) * 3.14f / 180.f) } *ProjectileSpeed * knockBackPercentage;
}




