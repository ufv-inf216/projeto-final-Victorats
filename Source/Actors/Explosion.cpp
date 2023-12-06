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
    // Implemente a lógica para renderizar a explosão em forma de cruz aqui
}