#include "pch.h"
#include "Player.h"
#include <iostream>

#define TO_RADIAN(x) x * (3.1415f/180.f)
Player::Player():
	m_pPossessedObject(nullptr), m_lookingDirection(Vector2f{})
{
}

void Player::Draw() const
{
	utils::SetColor(Color4f{1.f,0.2f,0.2f,1.f});
	const float width{10.f};
	const float height{10.f};
	
	utils::DrawRect(Rectf{m_position.x-width/2.f,m_position.y - height / 2.f ,width ,height });
	const float length{100.f};
	const float directionAngle{- m_lookingDirection.AngleWith(Vector2f{1.0f,0.0f}) };
	const float angle{ TO_RADIAN(15.f) };
	std::cout << directionAngle << std::endl;

	utils::DrawLine(m_position.ToPoint2f(), (m_position + m_lookingDirection).ToPoint2f());
	utils::FillArc(m_position.ToPoint2f(), length,length, directionAngle - angle / 2.f, directionAngle + angle / 2.f);
}

void Player::Update(float elapsedSec)
{
	const float frictionCoefficient{1.0f};
	m_velocity *= (1-elapsedSec)*frictionCoefficient;
	HandleInput(elapsedSec);
	Entity::Update(elapsedSec);
}

void Player::LookAt(const Vector2f& target)
{
	m_lookingDirection = target - m_position;
}

void Player::Possess(GameObject* newPossesion)
{
	m_pPossessedObject = newPossesion;
}

Point2f Player::GetPosition() const
{
	return m_position.ToPoint2f();
}

void Player::HandleInput(float elapsedSec)
{
	 const Uint8* keyboardState =  SDL_GetKeyboardState(NULL);
	 const float movSpeed{200.f};
	 if (keyboardState[SDL_SCANCODE_UP]) {
		 m_velocity.y += movSpeed * elapsedSec;	 }
	 if (keyboardState[SDL_SCANCODE_DOWN]) {
		 m_velocity.y -= movSpeed * elapsedSec;
	 }
	 if (keyboardState[SDL_SCANCODE_LEFT]) {

		 m_velocity.x -= movSpeed * elapsedSec;
	 }
	 if (keyboardState[SDL_SCANCODE_RIGHT]) {
		 m_velocity.x += movSpeed * elapsedSec;
	 }
	 //int mouseX;
	 //int MouseY;
	 //SDL_GetMouseState(&mouseX, &MouseY);

	 //std::cout << Vector2f{ float(mouseX), float(MouseY) } << std::endl;
	 //m_lookingDirection = Vector2f{ float(mouseX),float(MouseY )} - m_position;
}
