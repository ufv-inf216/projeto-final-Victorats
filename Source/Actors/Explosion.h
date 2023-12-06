#pragma once
#include "Actor.h"

class Explosion : public Actor
{
public:
    Explosion(Game* game, const Vector2& position);

    void OnUpdate(float deltaTime) override;
    void RenderExplosion();

private:
    float mTimer;
    class DrawAnimatedComponent* mDrawComponent;
};