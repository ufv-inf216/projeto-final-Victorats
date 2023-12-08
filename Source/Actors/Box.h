#pragma once

#include "Actor.h"
#include <string>

class Box : public Actor
{
public:
    Box(Game* game,const std::string &texturePath,ColliderLayer layer);
    ~Box();
    void DestroyBox();

};
