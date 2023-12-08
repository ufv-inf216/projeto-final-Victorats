
#pragma once

#include "Actor.h"
#include <string>

class Floor : public Actor
{
public:
    Floor(Game* game,const std::string &texturePath,ColliderLayer layer, int drawOrder);
    ~Floor();
};
