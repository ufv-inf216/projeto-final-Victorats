//
// Created by Lucas N. Ferreira on 08/09/23.
//

#pragma once
#include "Actor.h"

class Pacman : public Actor
{
public:
    explicit Pacman(Game* game,  int _id,float forwardSpeed = 100.0f);

    void OnProcessInput(const Uint8* keyState) override;
    void OnUpdate(float deltaTime) override;

    void DetectCollision();
    void OnCollision(std::vector<AABBColliderComponent::Overlap>& responses) override;

    class PathNode* GetSpawnNode() const { return mSpawnNode; }
    void SetSpawnNode(class PathNode* node) { mSpawnNode = node; }
    float mDyingTimer;

    int mRange;

    class PathNode* GetPrevNode() const;
    Vector2 GetPointInFrontOf(float dist) const;

    void Start();

    void Die();
    bool IsDead() { return mIsDead; }
    void reduceBomb(){mQtBombs--;}

private:
    void UpdateAnimations();

    void BombCreator(const Vector2& position);
    bool mIsDead;
    float mForwardSpeed;
    int id;
    class PathNode* mSpawnNode;
    class PathNode* mPrevNode;


    int mQtBombs;
    float mBombTimer;
    int mBombLim;

    class RigidBodyComponent* mRigidBodyComponent;
    class DrawAnimatedComponent* mDrawComponent;
    class AABBColliderComponent* mColliderComponent;
};