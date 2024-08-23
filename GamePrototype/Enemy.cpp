#include "pch.h"
#include "Enemy.h"
#include "Player.h"

Player* Enemy::g_Target;
Texture* Enemy::g_basicEnemySpriteSheet;

Enemy::Enemy(Vector2f position):
	m_animationManager(g_basicEnemySpriteSheet),Entity::Entity(position)
{
	const float spriteWidth{ g_basicEnemySpriteSheet->GetWidth() / 4.0f };
	const float spriteHeight{ g_basicEnemySpriteSheet->GetHeight() / 5.0f };
	m_animationManager.AddAnimation("Idle", Point2f{0,0},
		spriteWidth,
		spriteHeight,
		4,0.2f , Animation::AnimationMode::looped);
	m_animationManager.AddAnimation("Walk", Point2f{ spriteHeight,0 },
		spriteWidth,
		spriteHeight,
		4, 0.1f, Animation::AnimationMode::looped);
	m_animationManager.AddAnimation("Attack", Point2f{ 2 * spriteHeight,0 },
		spriteWidth,
		spriteHeight,
		4, 0.1f);
	m_animationManager.AddAnimation("Hurt", Point2f{ spriteHeight* 3,0 },
		spriteWidth,
		spriteHeight,
		4, 0.1f);
	m_animationManager.AddAnimation("Death", Point2f{ spriteHeight * 4,0 },
		spriteWidth,
		spriteHeight,
		4, 0.1f);
}

void Enemy::Update(float elapsedSec)
{
	if (g_Target == nullptr) return;


	const float speed{100.f};
	m_Velocity = Vector2f{m_Position.ToPoint2f(),g_Target->GetPosition().ToPoint2f()}.Normalized() * speed;
	Vector2f directionVector{m_Position.ToPoint2f(),g_Target->GetPosition().ToPoint2f()};
	m_angle = -directionVector.AngleWith(Vector2f{ 1.0f,0.0f }) * 180.f / 3.14f +180.f;

	Entity::Update(elapsedSec);
	m_animationManager.Update(elapsedSec);

	if (utils::IsOverlapping(Circlef{ m_Position.ToPoint2f(),m_hitboxRadius }, Circlef{ g_Target->GetPosition().ToPoint2f(),g_Target->GetHitboxRadius() })) {
		m_Health -= 2;
		Attack(*g_Target, 1);
	}
}

void Enemy::Draw() const
{
	float width{ 50 }, height{ 50 };
	Rectf dst{ -width / 2.f,-height / 2.f ,width,height };
	const float scale{0.7f};

	glPushMatrix(); {
		
		glTranslatef(m_Position.x, m_Position.y, 0.f);
		glRotatef(m_angle, 0.f, 0.f, 1.f);
		glScalef(scale, scale,1.0f);
		m_animationManager.Draw(dst);

	}glPopMatrix();
	Entity::Draw();
}
