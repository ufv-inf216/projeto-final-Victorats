//
// Created by Lucas N. Ferreira on 28/09/23.
//

#pragma once

#include "Actor.h"


class Item : public Actor
{
public:
    enum Type
    {
        addRange,
        addBomb,
    };

    Item(Game* game, Type type, Vector2);
    ~Item();

    // Get the type of ghost this is
    Type GetType() const { return mType; }

private:
    Type mType;
    int mWidth;
    Vector2 position;
    class DrawAnimatedComponent* mDrawComponent;
    int mHeight;
};
