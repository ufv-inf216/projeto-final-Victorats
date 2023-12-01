//
// Created by Lucas N. Ferreira on 26/10/23.
//

#include "ChaseState.h"
#include "../Ghost.h"
#include "../../../Game.h"
#include "../../../Actors/Pacman.h"
#include "../../../Components/AIComponents/FSMComponent.h"

ChaseState::ChaseState(FSMComponent *fsm)
            :GhostState(fsm, "chase")
{

}

void ChaseState::Start()
{
    // TODO [Parte 5.1]: https://ufv-inf216.lucasnferreira.com/p5-pacman
    mGhost->SetForwardSpeed(90.0f);

}

PathNode* ChaseState::FindNextNode()
{
    PathNode *targetNode = FindTargetState();
    mGhost->SetTargetNode(targetNode);
    // Select next node
    PathNode *nextNode = nullptr;
    std::set<PathNode *> * ignoreNode = new std::set<PathNode*>;
    ignoreNode->insert(mGhost->GetPreviousNode()) ;
    std::set<PathNode::Type> * ignoreType =  new std::set<PathNode::Type>;
    ignoreType->insert(PathNode::Type::Ghost);
    // TODO [Parte 5.2]: https://ufv-inf216.lucasnferreira.com/p5-pacman
    nextNode =  FindNearestNode(mGhost->GetNextNode()->GetAdjacents(),mGhost->GetTargetNode()->GetPosition(),ignoreType,ignoreNode);
    if(!nextNode){
        ignoreNode->clear();
        ignoreType->clear();
        nextNode =  FindNearestNode(mGhost->GetNextNode()->GetAdjacents(),mGhost->GetTargetNode()->GetPosition(),ignoreType,ignoreNode);
    }
    delete ignoreNode;
    delete ignoreType;
    return nextNode;

}

PathNode* ChaseState::FindTargetState()
{
    PathNode *targetNode = nullptr;

    // TODO [Parte 5.3]: https://ufv-inf216.lucasnferreira.com/p5-pacman
    if(mGhost->GetType() == Ghost::Type::Blinky){
      targetNode =  mGhost->GetGame()->GetPlayer()->GetPrevNode();
    }
    if(mGhost->GetType() == Ghost::Type::Pinky){

        auto p =  mGhost->GetGame()->GetPlayer()->GetPointInFrontOf(80);
        std::set<PathNode *> * ignoreNode = new std::set<PathNode*>;
        std::set<PathNode::Type> * ignoreType =  new std::set<PathNode::Type>;
        ignoreType->insert(PathNode::Type::Ghost);
        ignoreType->insert(PathNode::Type::Tunnel);
        targetNode = FindNearestNode(mGhost->GetNextNode()->GetAdjacents(),p,ignoreType,ignoreNode);
        delete ignoreType;
        delete ignoreNode;
    }
   if(mGhost->GetType() == Ghost::Type::Inky){
        auto p =  mGhost->GetGame()->GetPlayer()->GetPointInFrontOf(40);
        auto v = p-mGhost->GetPosition();
        v *= 2;
        v += mGhost->GetPosition();
        std::set<PathNode *> * ignoreNode = new std::set<PathNode*>;
        std::set<PathNode::Type> * ignoreType =  new std::set<PathNode::Type>;
        ignoreType->insert(PathNode::Type::Ghost);
        ignoreType->insert(PathNode::Type::Tunnel);
        targetNode = FindNearestNode(mGhost->GetNextNode()->GetAdjacents(),v,ignoreType,ignoreNode);
        delete ignoreType;
        delete ignoreNode;
    }
    if(mGhost->GetType() == Ghost::Type::Clyde) {
        Vector2 dist(mGhost->GetPosition().x - mGhost->GetGame()->GetPlayer()->GetPosition().x,
                     mGhost->GetPosition().y - mGhost->GetGame()->GetPlayer()->GetPosition().y);

        if(dist.x + dist.y > 150)
            targetNode = mGhost->GetGame()->GetPlayer()->GetPrevNode();
        else targetNode = mGhost->GetScatterNode();
    }

    return targetNode;
}


void ChaseState::HandleStateTransition(float stateTime)
{
    // TODO [Parte 5.4]: https://ufv-inf216.lucasnferreira.com/p5-pacman
    if(stateTime > 20.0f)
    mFSM->SetState("scatter");
}