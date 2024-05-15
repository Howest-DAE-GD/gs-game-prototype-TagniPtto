#include "pch.h"
#include "Character.h"

void Character::ScanSurrounding(const std::vector<Entity*>& surrounding)
{
	const float radius{ 60.f };
	for (Entity* pe: surrounding) {
		if (Vector2f(m_position.ToPoint2f(),pe->GetPosition()).Length() < radius) {
			if (pe->IsSus()) {
				m_target = pe;
				return;
			}
		}
	}

}
