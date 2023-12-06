#include "Explosion.h"
#include "../Game.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"

Explosion::Explosion(Game* game, const Vector2& position, int range)
        :Actor(game)
        ,mRange(range)
{
    SetPosition(position);
    mDrawComponent = new DrawAnimatedComponent(this,"../Assets/Sprites/Explosion/explosionsprite.png","../Assets/Sprites/Explosion/explosionsprite.json");
    mDrawComponent->AddAnimation("explode", {0,1,2,3,4,5});

    mDrawComponent->SetAnimation("explode");
    mDrawComponent->SetAnimFPS(10.0f);

    mTimer = 3.0f;
}

void Explosion::OnUpdate(float deltaTime)
{
    mTimer -= deltaTime;
    if (mTimer <= 0.0f){
        SetState(ActorState::Destroy);
    }
}

void Explosion::RenderExplosion()
{
    mColliders = std::vector<ColliderComponent*>(9);
    mDrawComponents = std::vector<DrawAnimatedComponent*>(9);
    for (int i = 0; i < 9; i++) {
        Vector2 colliderPosition = position;
        if (i != 0) {
            int direction = i % 4;
            int distance = 32 * (i / 4 + 1);
            switch (direction) {
                case 0: colliderPosition.y -= distance; break; // Up
                case 1: colliderPosition.x += distance; break; // Right
                case 2: colliderPosition.y += distance; break; // Down
                case 3: colliderPosition.x -= distance; break; // Left
            }
        }
        mColliders[i] = new ColliderComponent(this, colliderPosition);
        mDrawComponents[i] = new DrawAnimatedComponent(this,"../Assets/Sprites/Explosion/explosionsprite.png","../Assets/Sprites/Explosion/explosionsprite.json");
        mDrawComponents[i]->AddAnimation("explode", {0,1,2,3,4,5});
        mDrawComponents[i]->SetAnimation("explode");
        mDrawComponents[i]->SetAnimFPS(10.0f);
    }
}