//
// Created by Lucas N. Ferreira on 26/10/23.
//

#include "ScatterState.h"
#include "../Ghost.h"
#include "../../../Components/AIComponents/FSMComponent.h"

ScatterState::ScatterState(FSMComponent *fsm)
            :GhostState(fsm, "scatter")
{

}

void ScatterState::Start()
{
    // TODO [Parte 4.1]: https://ufv-inf216.lucasnferreira.com/p5-pacman
    mGhost->SetTargetNode(mGhost->GetScatterNode());
    mGhost->SetForwardSpeed(90.0f);
}

PathNode* ScatterState::FindNextNode()
{
    PathNode *nextNode = nullptr;
    // TODO [Parte 4.2]: https://ufv-inf216.lucasnferreira.com/p5-pacman
    std::set<PathNode *> * ignoreNode = new std::set<PathNode*>;
    ignoreNode->insert(mGhost->GetPreviousNode()) ;
    std::set<PathNode::Type> * ignoreType =  new std::set<PathNode::Type>;
    ignoreType->insert(PathNode::Type::Tunnel);
    ignoreType->insert(PathNode::Type::Ghost);
    nextNode =  FindNearestNode(mGhost->GetNextNode()->GetAdjacents(),mGhost->GetTargetNode()->GetPosition(),ignoreType,ignoreNode);
    if(!nextNode){
       ignoreType->erase(PathNode::Type::Tunnel);
       nextNode =  FindNearestNode(mGhost->GetNextNode()->GetAdjacents(),mGhost->GetTargetNode()->GetPosition(),ignoreType,ignoreNode);

    }
    if(!nextNode){
        ignoreNode->clear();
        ignoreType->clear();
        nextNode =  FindNearestNode(mGhost->GetNextNode()->GetAdjacents(),mGhost->GetTargetNode()->GetPosition(),ignoreType,ignoreNode);

    }

    return nextNode;
}

void ScatterState::HandleStateTransition(float stateTime)
{
    // TODO [Parte 4.3]: https://ufv-inf216.lucasnferreira.com/p5-pacman
    if(stateTime > 5.0f)
        mFSM->SetState("chase");
}
