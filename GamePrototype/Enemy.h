#pragma once
#include "Entity.h"
#include "AnimationManager.h"

class Player;
class Texture;

class Enemy :
    public Entity
{
public:

    static Texture* g_basicEnemySpriteSheet;
    static Player* g_Target;
private:
    AnimationManager m_animationManager; 

public:
    Enemy(Vector2f position = {});
    void Update(float elapsedSec) override;
    void Draw() const override;


};

