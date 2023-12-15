//
// Created by Lucas N. Ferreira on 03/08/23.
//

#include "Item.h"
#include "../Game.h"
#include "../Components/DrawComponents/DrawSpriteComponent.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"
#include "../Components/ColliderComponents/AABBColliderComponent.h"

Item::Item(Game* game, Type type, Vector2 position)
        :Actor(game)
        ,mType(type)
        ,position(position)
{
    std::string texturePath = "../Assets/Sprites/Items/";
    std::string jsonPath = "../Assets/Sprites/Items/";
    SetPosition(position);

    int random = rand() % 2;
    switch (random)
    {
        case 0:
            texturePath += "maisRange.jpg";
            new DrawSpriteComponent (this, texturePath,32,32,10);
            break;

        case 1:
            texturePath += "maisQt.jpg";
            new DrawSpriteComponent (this, texturePath,32,32,1);
            break;

    }



    new AABBColliderComponent(this, 0, 0, mWidth, mHeight, ColliderLayer::Item);

    mGame->AddItem(this);
}

Item::~Item()
{
    mGame->RemoveItem(this);
}
