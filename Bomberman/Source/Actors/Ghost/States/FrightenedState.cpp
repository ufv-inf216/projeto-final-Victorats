//
// Created by Lucas N. Ferreira on 26/10/23.
//

#include "FrightenedState.h"
#include "../Ghost.h"
#include "../../../Game.h"
#include "../../../Actors/Pacman.h"
#include "../../../Components/AIComponents/FSMComponent.h"
#include "../../../Random.h"

FrightenedState::FrightenedState(FSMComponent *fsm)
        :GhostState(fsm, "frightened")
{

}

void FrightenedState::Start()
{
    // TODO [Parte 6.1]: https://ufv-inf216.lucasnferreira.com/p5-pacman
    mGhost->SetTargetNode(nullptr);
    mGhost->SetForwardSpeed(65.0f);
    auto aux = mGhost->GetPreviousNode();
    mGhost->SetPreviousNode(mGhost->GetNextNode());
    mGhost->SetNextNode(aux);
    UpdateDirection();


}

PathNode* FrightenedState::FindNextNode()
{
    PathNode *nextNode = nullptr;
    auto adjacents = mGhost->GetNextNode()->GetAdjacents();
    auto index =   Random::GetIntRange(0,adjacents.size()-1);
    if(adjacents[index]->GetType() == PathNode::Type::Default) {
        nextNode = adjacents[index];
        return nextNode;
    }
    index =   Random::GetIntRange(0,adjacents.size()-1);
    if(adjacents[index]->GetType() != PathNode::Type::Tunnel )
        nextNode = adjacents[index];
    else {
        index = Random::GetIntRange(0, adjacents.size() - 1);
        nextNode = adjacents[index];
    }

    return nextNode;
}

void FrightenedState::HandleStateTransition(float stateTime)
{
    // TODO [Parte 6.3]: https://ufv-inf216.lucasnferreira.com/p5-pacman
    if(stateTime > 7.0f)
        mFSM->SetState("scatter");
}