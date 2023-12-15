//
// Created by Lucas N. Ferreira on 03/08/23.
//

#include "Box.h"
#include "../Game.h"
#include "../Components/DrawComponents/DrawSpriteComponent.h"
#include "../Components/DrawComponents/DrawPolygonComponent.h"
#include "../Components/ColliderComponents/AABBColliderComponent.h"
#include "Item.h"
#include <random>
#include "../Random.h"

Box::Box(Game* game,const std::string &texturePath,ColliderLayer layer)
        :Actor(game)
{
    new AABBColliderComponent(this, 0, 0, 32, 32, layer);

//    auto v1 = mColliderComponent->GetMin();
//    auto v4 = mColliderComponent->GetMax();
//    Vector2 v2 = Vector2(v4.x, v1.y);
//    Vector2 v3 = Vector2(v1.x, v4.y);
//    std::vector<Vector2> vertices = { v1,v2, v4, v3 };
//
//    new DrawPolygonComponent(this, vertices);
    mGame->AddBox(this);
    new DrawSpriteComponent (this, "../Assets/Sprites/Blocks/Block"+texturePath+".png",32,32,7);

}

Box::~Box()
{
    mGame->RemoveBox(this);
}

void Box::DestroyBox()
{

    Random rand;
    int randomNumber = rand.GetIntRange(0,49);

    SetState(ActorState::Destroy);




        if(randomNumber == 3)
            new Item(mGame,Item::Type::addBomb,GetPosition());
        if(randomNumber == 6)
        new Item(mGame,Item::Type::addRange,GetPosition());


}
