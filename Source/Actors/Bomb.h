//
// Created by victo on 05/12/2023.
//
#pragma once
#include "Actor.h"
#include "Pacman.h"

class Bomb : public Actor
{
public:


    Bomb(Game* game, const Vector2& position, Pacman* dono, int range);
    ~Bomb();

    void OnUpdate(float deltaTime);

private:
    Pacman* mOwner;
    class DrawAnimatedComponent* mDrawComponent;
    float mTimer;
    const Vector2& mPosition;
    int mRange;
};


