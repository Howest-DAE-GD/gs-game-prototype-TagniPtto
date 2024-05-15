#pragma once

#include "utils.h"


class Entity
{
public:
	explicit Entity();
	explicit Entity(Vector2f position, Vector2f velocity);
	virtual void Update(float elapsedSec);
	virtual void Draw()const;
	Point2f GetPosition() const;
	bool IsSus()const;


protected:
	Vector2f m_velocity;
	Vector2f m_position;
	float m_torque;
	float hitBoxRadius;
	
	bool beingSus;
};

