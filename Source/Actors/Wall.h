//
// Created by Lucas N. Ferreira on 28/09/23.
//

#pragma once

#include "Actor.h"
#include <string>

class Wall : public Actor
{
public:
    Wall(Game* game,const std::string &texturePath,ColliderLayer layer);
    ~Wall();
};
