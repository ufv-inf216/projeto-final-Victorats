//
// Created by victo on 05/12/2023.
//

#include "Bomb.h"
#include "../Game.h"
#include "../Components/DrawComponents/DrawSpriteComponent.h"
#include "../Components/DrawComponents/DrawPolygonComponent.h"
#include "../Components/ColliderComponents/AABBColliderComponent.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"


Bomb::Bomb(Game* game, const Vector2& position, Pacman* dono)
        :Actor(game)
        ,mOwner(dono)
        ,mPosition(position)
        {

            SetPosition(position);
            mDrawComponent = new DrawAnimatedComponent(this,"../Assets/Sprites/Bomb/bombsprite.png","../Assets/Sprites/Bomb/bombsprite.json");
            mDrawComponent->AddAnimation("tictac", {0,1,2,3,4,5});

            mDrawComponent->SetAnimation("tictac");
            mDrawComponent->SetAnimFPS(10.0f);

            new AABBColliderComponent(this, 0, 0, 32, 32, ColliderLayer::Bomb);


            mTimer = 3.0f;
        }

void Bomb::OnUpdate(float deltaTime)
    {
        mTimer -= deltaTime;
        if (mTimer <= 0.0f){
            mOwner->reduceBomb();
            //new Explosion(GetGame(), GetPosition());
            SetState(ActorState::Destroy);

        }
    }