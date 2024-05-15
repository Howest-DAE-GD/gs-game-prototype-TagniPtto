#include "pch.h"
#include "GameObject.h"



void GameObject::Collistion(GameObject& other)
{
	std::vector<Point2f> intersection;
	if (utils::IntersectPolygons(this->m_HitBox, other.m_HitBox, intersection)) {
		Vector2f r{ utils::AverageBetweenPoints(intersection) };
		this->m_velocity += (r - this->m_position).Normalized() /(r - this->m_position).Norm();
		other.m_velocity += (r - other.m_position).Normalized() /(r - other.m_position).Norm();
	}
	
}

GameObject::GameObject():
	GameObject(Vector2f{}, Vector2f{float(std::rand()%40-20),float(std::rand()%40-20)})
{

}

GameObject::GameObject(Vector2f position, Vector2f velocity):
	Entity(position,velocity), m_pTexture(nullptr)
{
	const float size{ 10.f };
	m_HitBox.push_back(Point2f{ -size,size });
	m_HitBox.push_back(Point2f{ size,size });
	m_HitBox.push_back(Point2f{ size,-size });
	m_HitBox.push_back(Point2f{ -size,-size });
}

void GameObject::Update(float elapsedSec)
{
	Entity::Update(elapsedSec);

}

void GameObject::Draw() const
{

	utils::SetColor(Color4f{0.f,1.f,0.1f,1.f});
	glPushMatrix(); {
	glTranslatef(m_position.x, m_position.y,1.f);
	utils::DrawPolygon(m_HitBox);

	}
	glPopMatrix();
	//glTranslatef(-m_position.x, -m_position.y,1.f);
}

void GameObject::SetPosition(Point2f position)
{
	m_position = Vector2f{ position };
}
