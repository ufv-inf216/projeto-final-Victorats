//
// Created by Lucas N. Ferreira on 03/08/23.
//

#include "Wall.h"
#include "../Game.h"
#include "../Components/DrawComponents/DrawSpriteComponent.h"
#include "../Components/DrawComponents/DrawPolygonComponent.h"
#include "../Components/ColliderComponents/AABBColliderComponent.h"

Wall::Wall(Game* game,const std::string &texturePath,ColliderLayer layer, int drawOrder)
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
    mGame->AddWall(this);
    new DrawSpriteComponent (this, "../Assets/Sprites/Blocks/Block"+texturePath+".jpg",32,32,5);

}

Wall::~Wall()
{
    mGame->RemoveWall(this);
}