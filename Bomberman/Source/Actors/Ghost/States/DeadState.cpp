//
// Created by Lucas N. Ferreira on 26/10/23.
//

#include "DeadState.h"
#include "../Ghost.h"
#include "../../../Game.h"
#include "../../../Actors/Pacman.h"
#include "../../../Components/AIComponents/FSMComponent.h"
#include "../../../Random.h"

DeadState::DeadState(FSMComponent *fsm)
        :GhostState(fsm, "dead")
{

}

void DeadState::Start()
{
    // TODO [Parte 7.1]: https://ufv-inf216.lucasnferreira.com/p5-pacman
    mGhost->SetTargetNode(mGhost->GetGame()->GetGhostPen());
    mGhost->SetForwardSpeed(125.0f);
}

PathNode* DeadState::FindNextNode()
{
    PathNode *nextNode = nullptr;

    // TODO [Parte 7.2]: https://ufv-inf216.lucasnferreira.com/p5-pacman
    std::set<PathNode*> *ignoreNode = new std::set<PathNode*>;
    ignoreNode->insert(mGhost->GetPreviousNode());
    std::set<PathNode::Type>*ignoreType = new std::set<PathNode::Type>;;
    ignoreType->insert(PathNode::Type::Default);
    ignoreType->insert(PathNode::Type::Tunnel);
    nextNode = FindNearestNode(mGhost->GetNextNode()->GetAdjacents(), mGhost->GetTargetNode()->GetPosition(), ignoreType, ignoreNode);


    if (!nextNode)
    {
        ignoreType->erase(PathNode::Type::Default);
        nextNode = FindNearestNode(mGhost->GetNextNode()->GetAdjacents(), mGhost->GetTargetNode()->GetPosition(), ignoreType, ignoreNode);
    }

    if (!nextNode)
    {
        ignoreType->clear();
        ignoreNode->clear();
        nextNode = FindNearestNode(mGhost->GetNextNode()->GetAdjacents(), mGhost->GetTargetNode()->GetPosition(), ignoreType, ignoreNode);
    }
    delete ignoreNode;
    delete ignoreType;
    return nextNode;

}


void DeadState::HandleStateTransition(float stateTime)
{
    // TODO [Parte 7.3]: https://ufv-inf216.lucasnferreira.com/p5-pacman]
    auto x = mGhost->GetGame()->GetGhostPen()->GetComponent<AABBColliderComponent>();
    if(mGhost->GetComponent<AABBColliderComponent>()->Intersect(*x))
        mFSM->SetState("scatter");
}