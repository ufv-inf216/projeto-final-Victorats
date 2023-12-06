#include "Explosion.h"
#include "../Game.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"

Explosion::Explosion(Game* game, const Vector2& position)
        :Actor(game)

{
    SetPosition(position);
    mDrawComponent = new DrawAnimatedComponent(this,"../Assets/Sprites/Explosion/exp.png","../Assets/Sprites/Explosion/exp.json");
    mDrawComponent->AddAnimation("explode", {0,1});

    mDrawComponent->SetAnimation("explode");
    mDrawComponent->SetAnimFPS(150.0f);

    mTimer = 3.0f;
}



void Explosion::OnUpdate(float deltaTime)
{
    mTimer -= deltaTime;
    if (mTimer <= 0.0f){
        SetState(ActorState::Destroy);
    }
}