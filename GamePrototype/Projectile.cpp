#include "pch.h"
#include "Projectile.h"

#include "Texture.h"
#include "Enemy.h"

Texture* Projectile::g_pBasicProjectileTexture;

Projectile::Projectile(Vector2f position, Vector2f velocity, float angle, Entity* parent = nullptr):
	Entity::Entity(position, velocity , angle, g_pBasicProjectileTexture),m_pParent(parent)
{
	if (Projectile::g_pBasicProjectileTexture == nullptr) {
		Projectile::g_pBasicProjectileTexture = new Texture("BasicProjectile.png");
	}
}

void Projectile::Update(float elapsedSec, std::list<Enemy*>& enemies)
{

	Entity::Update(elapsedSec);
	for (Enemy*& e: enemies) {
		if (utils::IsOverlapping(Circlef{m_Position.ToPoint2f(),m_hitboxRadius}, Circlef{ e->GetPosition().ToPoint2f(),e->GetHitboxRadius()})) {
			m_Health -= 2;
			Attack(*e,5);
		}
	}
	//TODO: check if overlapping with enemys
}

void Projectile::Draw() const
{
	Entity::Draw();
}

void Projectile::SetParent(Entity* parent)
{
	m_pParent = parent;
}
