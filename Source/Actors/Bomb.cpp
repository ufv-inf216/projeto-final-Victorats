//
// Created by victo on 05/12/2023.
//

#include "Bomb.h"
#include "../Game.h"
#include "../Components/DrawComponents/DrawSpriteComponent.h"
#include "Wall.h"

#include "../Components/DrawComponents/DrawAnimatedComponent.h"
#include "../Actors/Explosion.h"


Bomb::Bomb(Game* game, const Vector2& position, Pacman* dono, int range)
        :Actor(game)
        ,mOwner(dono)
        ,mPosition(position)
        ,mRange(range) {
    Vector2 posicao;
    int distancia = 987654321;
    for (int i = 0; i < mGame->mBombPositions.size(); i++) {
        int temp = abs(mGame->mBombPositions[i].x - position.x) + abs(mGame->mBombPositions[i].y - position.y);
        if (temp < distancia) {
            distancia = temp;
            posicao.x = mGame->mBombPositions[i].x;
            posicao.y = mGame->mBombPositions[i].y;
        }

        SetPosition(posicao);

        mDrawComponent = new DrawAnimatedComponent(this, "../Assets/Sprites/Bomb/bombsprite.png",
                                                   "../Assets/Sprites/Bomb/bombsprite.json");
        mDrawComponent->AddAnimation("tictac", {0, 1, 2, 3, 4, 5});

        mDrawComponent->SetAnimation("tictac");
        mDrawComponent->SetAnimFPS(10.0f);

        new AABBColliderComponent(this, 0, 0, 32, 32, ColliderLayer::Bomb);


        mTimer = 3.0f;
    }
}

Bomb::~Bomb(){

            mGame->RemoveBomb(this);
        }

void Bomb::OnUpdate(float deltaTime)
    {
        mTimer -= deltaTime;
        if (mTimer <= 0.0f){


            mOwner->reduceBomb();
            new Explosion(GetGame(), GetPosition());

            for(int i = 1; i <= mRange; i++) {
                Vector2 top = GetPosition() + Vector2(0, i * 32);
                bool naoC = false;


                for(auto parede : mGame->GetWalls()) {
                    if(parede->GetPosition().x == top.x && parede->GetPosition().y == top.y) {
                        naoC = true;
                    }
                }

                if(naoC) {
                    break;
                }

                new Explosion(GetGame(), top);
            }
            for(int i = 1; i<=mRange; i++) {
                Vector2 left = GetPosition() + Vector2(i * (-32), 0);
                bool naoC = false;


                for(auto parede : mGame->GetWalls()) {
                    if(parede->GetPosition().x == left.x && parede->GetPosition().y == left.y) {
                        naoC = true;
                    }
                }

                if(naoC) {
                    break;
                }

                new Explosion(GetGame(), left);
            }
            for(int i = 1; i<=mRange; i++) {
                Vector2 right = GetPosition() + Vector2(i*(+32), 0);
                bool naoC = false;

                for(auto parede : mGame->GetWalls()) {
                    if(parede->GetPosition().x == right.x && parede->GetPosition().y == right.y) {
                      naoC = true;
                    }
                }

                if(naoC) {
                    break;
                }

                new Explosion(GetGame(), right);
            }
            for(int i = 1; i<=mRange; i++) {
                Vector2 down = GetPosition() + Vector2(0, i*(-32));
                bool naoC = false;

                for(auto parede : mGame->GetWalls()) {
                    if(parede->GetPosition().x == down.x && parede->GetPosition().y == down.y) {
                        naoC = true;
                    }
                }

                if(naoC) {
                    break;
                }
                    new Explosion(GetGame(), down);
            }

            SetState(ActorState::Destroy);

        }
    }




