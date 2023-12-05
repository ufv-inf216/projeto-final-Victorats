//
// Created by Lucas N. Ferreira on 03/08/23.
//
#include "Pacman.h"
#include "../Game.h"
#include "../Actors/Item.h"
#include "../Actors/Wall.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"


Pacman::Pacman(Game* game, int _id,
               const float forwardSpeed)
        :Actor(game)
        ,mForwardSpeed(forwardSpeed)
        ,mIsDead(false)
        , mSpawnNode(nullptr)
{   id = _id;
    mDrawComponent = new DrawAnimatedComponent(this, "../Assets/Sprites/Pacman/globinsprite2.png", "../Assets/Sprites/Pacman/goblin.json");
    mDrawComponent->AddAnimation("idle", {0});
    mDrawComponent->AddAnimation("dead", {0});
    mDrawComponent->AddAnimation("right", {4,5,6,7});
    mDrawComponent->AddAnimation("up", {8,9});
    mDrawComponent->AddAnimation("down", {1,2,3});

    mDrawComponent->SetAnimation("idle");
    mDrawComponent->SetAnimFPS(10.0f);
    mRigidBodyComponent = new RigidBodyComponent(this);
    mColliderComponent = new AABBColliderComponent(this, 0, 0, 32, 32, ColliderLayer::Player);
<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
//    auto v1 = mColliderComponent->GetMin();
//    auto v4 = mColliderComponent->GetMax();
//
//    Vector2 v2 = Vector2(v4.x, v1.y);
//    Vector2 v3 = Vector2(v1.x, v4.y);
//
//    // Put them into array
//    std::vector<Vector2> vertices = { v1,v2, v4, v3 };
//
//    new DrawPolygonComponent(this, vertices);
}

void Pacman::OnProcessInput(const uint8_t* state)
{
    if(id == 1) {
        if (state[SDL_SCANCODE_D]) {
            mRigidBodyComponent->SetVelocity(Vector2(mForwardSpeed, 0));
            mRotation = 0;
        } else if (state[SDL_SCANCODE_A]) {
            mRigidBodyComponent->SetVelocity(Vector2(-mForwardSpeed, 0));
            mRotation = Math::Pi;
        } else {
            mRigidBodyComponent->SetVelocity(Vector2(0, mRigidBodyComponent->GetVelocity().y));
        }

        if (state[SDL_SCANCODE_W]) {
            mRigidBodyComponent->SetVelocity(Vector2(mRigidBodyComponent->GetVelocity().x, -mForwardSpeed));
        } else if (state[SDL_SCANCODE_S]) {
            mRigidBodyComponent->SetVelocity(Vector2(mRigidBodyComponent->GetVelocity().x, mForwardSpeed));
        } else {
            mRigidBodyComponent->SetVelocity(Vector2(mRigidBodyComponent->GetVelocity().x, 0));
        }
    }
    else if (id == 2){
        if (state[SDL_SCANCODE_RIGHT]) {
            mRigidBodyComponent->SetVelocity(Vector2(mForwardSpeed, 0));
            mRotation = 0;
        } else if (state[SDL_SCANCODE_LEFT]) {
            mRigidBodyComponent->SetVelocity(Vector2(-mForwardSpeed, 0));
            mRotation = Math::Pi;
        } else {
            mRigidBodyComponent->SetVelocity(Vector2(0, mRigidBodyComponent->GetVelocity().y));
        }

        if (state[SDL_SCANCODE_UP]) {
            mRigidBodyComponent->SetVelocity(Vector2(mRigidBodyComponent->GetVelocity().x, -mForwardSpeed));
        } else if (state[SDL_SCANCODE_DOWN]) {
            mRigidBodyComponent->SetVelocity(Vector2(mRigidBodyComponent->GetVelocity().x, mForwardSpeed));
        } else {
            mRigidBodyComponent->SetVelocity(Vector2(mRigidBodyComponent->GetVelocity().x, 0));
        }

    }
}

void Pacman::OnUpdate(float deltaTime)
{
    if(mGame->GetGameState() != Game::State::Started) {
        return;
    }

    // Detect and resolve collisions
    DetectCollision();

    // Pacman controls
    Vector2 velocity = mRigidBodyComponent->GetVelocity();

    if(velocity.y == 0.f) {
        if (velocity.x > 0.f) {
            mCurrentDirection = Vector2::UnitX;
            mDrawComponent->FlipHorizontally(false);
        }
        else if (velocity.x < 0.f) {
            mCurrentDirection = Vector2::NegUnitX;
            mDrawComponent->FlipHorizontally(true);
        }
    }
    else {
        if (velocity.y > 0.f) {
            mCurrentDirection = Vector2::NegUnitY;
            mDrawComponent->FlipVertically(false);
            if(velocity.x < 0.f) {
                mCurrentDirection = Vector2::NegUnitX;
                mDrawComponent->FlipHorizontally(true);
            }
        }
        else if (velocity.y < 0.f) {
            mCurrentDirection = Vector2::UnitY;
            mDrawComponent->FlipVertically(false);

            if(velocity.x < 0.f) {
                mCurrentDirection = Vector2::NegUnitX;
                mDrawComponent->FlipHorizontally(true);
            }
        }
    }

    UpdateAnimations();
}

void Pacman::Die()
{
    mIsDead = true;
    mRigidBodyComponent->SetVelocity(Vector2::Zero);
    mRigidBodyComponent->SetEnabled(false);
    mColliderComponent->SetEnabled(false);
}

void Pacman::Start()
{
    mIsDead = false;
    mRigidBodyComponent->SetVelocity(Vector2::Zero);
    mRigidBodyComponent->SetEnabled(true);
    mColliderComponent->SetEnabled(true);
    mDrawComponent->SetAnimation("idle");

}

void Pacman::UpdateAnimations()
{
    Vector2 velocity = mRigidBodyComponent->GetVelocity();

    if(mIsDead) {
        mDrawComponent->SetIsPaused(false);
        SetDirection(Vector2::UnitY);
        mDrawComponent->SetAnimation("dead");
    }
    else {
        if(velocity.x != .0f) {
            mDrawComponent->SetAnimation("right");
            mDrawComponent->SetIsPaused(false);
        }
        else if(velocity.y < .0f) {
            mDrawComponent->SetAnimation("up");
            mDrawComponent->SetIsPaused(false);
        }
        else if(velocity.y > .0f) {
            mDrawComponent->SetAnimation("down");
            mDrawComponent->SetIsPaused(false);
        }
        else {
            mDrawComponent->SetIsPaused(true);
            mDrawComponent->ResetAnim();
        }
    }
}

void Pacman::DetectCollision()
{
    // Check collision against walls, items and ghosts
    std::vector<AABBColliderComponent *> colliders;

    for(auto *wall : mGame->GetWalls()) {
        colliders.emplace_back(wall->GetComponent<AABBColliderComponent>());
    }

    for(auto *item : mGame->GetItems()) {
        colliders.emplace_back(item->GetComponent<AABBColliderComponent>());
    }

    mColliderComponent->DetectCollision(mRigidBodyComponent, colliders);
}

void Pacman::OnCollision(std::vector<AABBColliderComponent::Overlap>& responses)
{
    for(auto collision : responses)
    {
        if(collision.target->GetLayer() == ColliderLayer::Item)
        {
            auto *item = dynamic_cast<Item *>(collision.target->GetOwner());

            if(item->GetType() == Item::Type::Pellet)
            {
                // Destroy power pellet
                collision.target->GetOwner()->SetState(ActorState::Destroy);
            }
            else if(item->GetType() == Item::Type::PowerPellet)
            {
                // Destroy power pellet
                collision.target->GetOwner()->SetState(ActorState::Destroy);

            }
        }

    }
}

PathNode* Pacman::GetPrevNode() const
{
    return mPrevNode;
}

Vector2 Pacman::GetPointInFrontOf(float dist) const
{
    Vector2 facingDirection;
    Vector2 velocity = mRigidBodyComponent->GetVelocity();

    if (velocity.y < 0.0f) {
        facingDirection = Vector2::NegUnitY;
    }
    else if (velocity.y > 0.0f) {
        facingDirection = Vector2::UnitY;
    }
    else if (velocity.x > 0.0f) {
        facingDirection = Vector2::UnitX;
    }
    else {
        facingDirection = Vector2::NegUnitX;
    }

    return (GetPosition() + facingDirection * dist);
}
