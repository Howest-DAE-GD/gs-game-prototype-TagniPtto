#pragma once
#include "Entity.h"
#include "Texture.h"
#include <vector>
class GameObject : public Entity

{
public:
	explicit GameObject();
	explicit GameObject(Vector2f position, Vector2f velocity = Vector2f{0.f,0.f});
	virtual void Update(float elapsedSec) override;
	virtual void Draw() const override;
	virtual void SetPosition(Point2f position);
	void Collistion(GameObject& other);

private:

	Texture* m_pTexture;
	std::vector<Point2f> m_HitBox;
};

