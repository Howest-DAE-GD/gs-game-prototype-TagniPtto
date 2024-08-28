#include "pch.h"
#include "GravityOrb.h"
#include "Enemy.h"
#include "Projectile.h"
#include "utils.h"
#include <iostream>
#include "Texture.h"


Texture* GravityOrb::g_orbTexture;


GravityOrb::GravityOrb(Vector2f position, Vector2f velocity, float angle, Entity* parent, float force, float rotationForce) :
	Projectile::Projectile(position, velocity.Normalized()* GetProjectileSpeed(), angle, parent),
	m_force(force),
	m_rotationForce(rotationForce),
	m_animManager(g_orbTexture)
	
{
	float spriteWidth{ g_orbTexture->GetWidth()/5.0f};
	float spriteHeight{g_orbTexture->GetHeight()/6.0f};
	m_animManager.AddAnimation("main", Point2f{},spriteWidth,spriteHeight,5*6,0.03f,Animation::AnimationMode::looped);
	m_lifeTime = 3.f;
}

void GravityOrb::Update(float elapsedSec, std::list<Enemy*>& enemies, std::list<Projectile*>& projectiles)
{
	Entity::Update(elapsedSec);
	m_animManager.Update(elapsedSec);
	m_timer += elapsedSec;
	const float x{ ((3 * m_timer / m_lifeTime) - 1) };
	m_hitboxRadius = 250.f * std::abs(float(expf(-2 * (x * x))));
	m_textureDispaySize = 250.f * std::abs(float(expf(-2* (x * x))));
	//m_angularVelocity = std::signbit(m_angularVelocity)*250.f * std::abs(float(expf(-2 * (x * x))));

	const float radius{ m_hitboxRadius };
	for (Enemy*& e : enemies) {
		if (utils::IsOverlapping(Circlef{ m_Position.ToPoint2f(), m_hitboxRadius }, Circlef{ e->GetPosition().ToPoint2f(),e->GetHitboxRadius() })) {
			

			Vector2f dir{ m_Position.ToPoint2f() , e->GetPosition().ToPoint2f() };
			
			const float u{ m_hitboxRadius /10 };
			//const float resultingForce{ force * expf(-(dir.Norm() * dir.Norm()/(u*u)))};
			const float resultingForce{ m_force * powf(1,-(dir.Norm() * dir.Norm()/(u*u)))};
			//const float resultingtForce{ rotationForce * expf(-(dir.Norm() * dir.Norm()/u*u))};
			const float resultingtForce{ m_rotationForce * powf(1,-(dir.Norm() * dir.Norm()/u*u))};
			Vector2f f{ - dir.Normalized()* resultingForce +  m_angularVelocity/std::abs(m_angularVelocity)* dir.Orthogonal().Normalized() * resultingtForce };
			std::cout << "Force : " << f << std::endl;
			e->SetForce(f);
			Attack(*e, 10.f/(dir.Norm()));
		}
	}
	if (m_lifeTime == 0 ) {
		m_Health = 0;
	}
}

void GravityOrb::Draw() const
{
	glPushMatrix(); {

		glTranslatef(m_Position.x, m_Position.y, 0.f);
		glRotatef(m_angle, 0.f, 0.f, 1.f);
		const float percentage{ m_timer / m_lifeTime };
		const float rPercentage{ m_timer / m_lifeTime };
		const float lightness{ logDeclineFunction(1.f / 5.f,percentage) };
		const float alpha{ logDeclineFunction(1.f / 4.f,percentage) };

		const float r{ 255.f };
		const float g{ logDeclineFunction(1.f / 2.f,percentage) * 240.f };
		const float b{ rPercentage * 66.f };

		Color4f c{ (lightness * r) / 255.f,
					(lightness * g) / 255.f,
					(lightness * b) / 255.f, alpha };

		m_animManager.Draw(Rectf{ -m_textureDispaySize / 2.f ,-m_textureDispaySize / 2.f ,m_textureDispaySize ,m_textureDispaySize });
		glRotatef(m_angle* 2.0f, 0.f, 0.f, 1.f);
		m_animManager.Draw(Rectf{ -m_textureDispaySize / 2.f ,-m_textureDispaySize / 2.f ,m_textureDispaySize ,m_textureDispaySize },15);
		//glRotatef(m_angle* 2.0f, 0.f, 0.f, 1.f);
		//glScalef(0.7f, 0.7f, 1.0f);
		//m_animManager.Draw(Rectf{ -m_textureDispaySize / 2.f ,-m_textureDispaySize / 2.f ,m_textureDispaySize ,m_textureDispaySize });
		utils::SetColor(c);
		//utils::DrawEllipse(Ellipsef{ {},m_hitboxRadius, m_hitboxRadius });
		
	}glPopMatrix();
}

Projectile* GravityOrb::Clone() const
{
	return new GravityOrb(*this);
}

float GravityOrb::GetProjectileSpeed()
{
	return 100.f;
}
