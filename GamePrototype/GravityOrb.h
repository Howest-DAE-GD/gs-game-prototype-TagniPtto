#pragma once
#include "Projectile.h"
#include "AnimationManager.h"

class GravityOrb :
    public Projectile
    
{
public:
    const float m_force{ };
    const float m_rotationForce{  };
    static Texture* g_orbTexture;

    AnimationManager m_animManager;

public:

    GravityOrb(Vector2f position, Vector2f velocity, float angle, Entity* parent = nullptr , float force = 12000.f,float rotationForce = 10000.f);
    GravityOrb(const GravityOrb& other) = default;


    virtual void Update(float elapsedSec, std::list<Enemy*>& enemies, std::list<Projectile*>& projectiles) override;
    virtual void Draw()const override;

    virtual Projectile* Clone() const override;
    virtual float GetProjectileSpeed() override;
};

