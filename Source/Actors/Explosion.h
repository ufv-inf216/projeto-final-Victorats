#pragma once
#include "Actor.h"

class Explosion : public Actor
{
public:
    Explosion(Game* game, const Vector2& position, int range);

    void OnUpdate(float deltaTime) override;
    void RenderExplosion();

private:
    float mTimer;
    int mRange;
    class DrawAnimatedComponent* mDrawComponent;
};