#include "Explosion.h"
#include "../Game.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"
#include "Box.h"

Explosion::Explosion(Game* game, const Vector2& position)
        :Actor(game)

{
    SetPosition(position);
    mDrawComponent = new DrawAnimatedComponent(this,"../Assets/Sprites/Explosion/exp.png","../Assets/Sprites/Explosion/exp.json");
    mDrawComponent->AddAnimation("explode", {0,1});

    mDrawComponent->SetAnimation("explode");
    mDrawComponent->SetAnimFPS(150.0f);

    mRigidBodyComponent = new RigidBodyComponent(this);
    mColliderComponent = new AABBColliderComponent(this, 0, 0, 32, 32, ColliderLayer::Explosion);

    mTimer = 1.5f;
}



void Explosion::OnUpdate(float deltaTime)
{
    mTimer -= deltaTime;
    if (mTimer <= 0.0f){
        mGame->RemoveExplosion(this);
        SetState(ActorState::Destroy);

    }

    DetectCollisions();

}

void Explosion::DetectCollisions() {

    // Check collision against walls, items and ghosts
    std::vector<AABBColliderComponent *> colliders;

    for(auto *box : mGame->Getbox()) {
        colliders.emplace_back(box->GetComponent<AABBColliderComponent>());
    }

    mColliderComponent->DetectCollision(mRigidBodyComponent, colliders);


}

void Explosion::OnCollision(std::vector<AABBColliderComponent::Overlap>& responses)
{
    for(auto collision : responses)
    {


        if(collision.target->GetLayer() == ColliderLayer::Box)
        {
            // quebra
            for(auto x : mGame->Getbox()){
                if(collision.target->GetOwner() == x){
                    x->DestroyBox();
                }
            }
        }


    }
}


