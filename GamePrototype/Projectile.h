#pragma once
#include "Entity.h"
#include <list>


class Enemy;
class Projectile : public Entity
{
public:
	static Texture* g_pBasicProjectileTexture;
	Entity* m_pParent{nullptr};

public:
	Projectile(Vector2f position,Vector2f velocity,float angle, Entity* parent);
	virtual void Update(float elapsedSec , std::list<Enemy*>& enemies);
	virtual void Draw()const override;
	void SetParent(Entity* parent);
};


