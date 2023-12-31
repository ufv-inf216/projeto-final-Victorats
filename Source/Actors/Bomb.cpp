//
// Created by victo on 05/12/2023.
//

#include "Bomb.h"
#include "../Game.h"
#include "../Components/DrawComponents/DrawSpriteComponent.h"
#include "Wall.h"
#include "../AudioSystem.h"
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

            mGame->mAudio->PlaySound("bomb.mp3");


            mOwner->reduceBomb();
            new Explosion(GetGame(), GetPosition());

            for(int i = 1; i <= mRange; i++) {
                Vector2 top = GetPosition() + Vector2(0, i * 32);
                bool naoC = false;


                for(auto parede : mGame->mExplosionPositions) {
                    if(parede.x == top.x && parede.y == top.y) {
                        naoC = true;
                        break;
                    }
                }

                for(auto caixa : mGame->mBoxPositions) {
                    if(caixa.x == top.x && caixa.y == top.y) {
                        naoC = true;
                        new Explosion(GetGame(), top);
                        break;
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


                for(auto parede : mGame->mExplosionPositions) {
                    if(parede.x == left.x && parede.y == left.y) {
                        naoC = true;
                        break;
                    }
                }
                for(auto caixa : mGame->mBoxPositions) {
                    if(caixa.x == left.x && caixa.y == left.y) {
                        new Explosion(GetGame(), left);
                        naoC = true;
                        break;
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

                for(auto parede : mGame->mExplosionPositions) {
                    if(parede.x == right.x && parede.y == right.y) {
                        naoC = true;
                        break;
                    }
                }
                for(auto caixa : mGame->mBoxPositions) {
                    if(caixa.x == right.x && caixa.y == right.y) {
                        naoC = true;
                        new Explosion(GetGame(), right);
                        break;
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

                for(auto parede : mGame->mExplosionPositions) {
                    if(parede.x == down.x && parede.y == down.y) {
                        naoC = true;
                    }
                }
                for(auto caixa : mGame->mBoxPositions) {
                    if(caixa.x == down.x && caixa.y == down.y) {
                        naoC = true;
                        new Explosion(GetGame(), down);
                        break;
                    }
                }

                if(naoC) {
                    break;
                }
                    new Explosion(GetGame(), down);
            }

            SetState(ActorState::Destroy);

        }
        mGame->mAudio->CacheAllSounds();
    }




