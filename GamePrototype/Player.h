#pragma once
#include "Entity.h"

class Level;
class GameObject;
class Player:public Entity
{
public:
	Player();
	void Draw() const override;
	void Update(float elapsedSec) override;
	void LookAt(const Vector2f& target);


	void Possess(GameObject* newPossesion);
	Point2f GetPosition() const;


private:
	void HandleInput(float elapsedSec);

	Vector2f m_lookingDirection{0,0};

	Level* m_pcurrentLevel{nullptr};
	GameObject* m_pPossessedObject{nullptr};
};

