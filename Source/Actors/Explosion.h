#pragma once
#include "Actor.h"

class Explosion : public Actor
{
public:

    Explosion(Game* game, const Vector2& position);
    ~Explosion();

    void OnUpdate(float deltaTime) override;

    void DetectCollisions();
    void OnCollision(std::vector<AABBColliderComponent::Overlap>& responses) override;

private:
    float mTimer;
    class DrawAnimatedComponent* mDrawComponent;
    class AABBColliderComponent* mColliderComponent;
    class RigidBodyComponent* mRigidBodyComponent;
};