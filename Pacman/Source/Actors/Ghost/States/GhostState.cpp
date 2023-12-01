//
// Created by Lucas N. Ferreira on 26/10/23.
//

#include "GhostState.h"
#include "../Ghost.h"
#include "../../../Game.h"
#include "../../../Components/AIComponents/FSMComponent.h"
#include <cfloat>

GhostState::GhostState(class FSMComponent *fsm, const std::string &name)
        : FSMState(fsm, name)
{
    mGhost = dynamic_cast<Ghost *>(mFSM->GetOwner());
}

void GhostState::Update(float deltaTime)
{
    // TODO [Parte 3.1]: https://ufv-inf216.lucasnferreira.com/p5-pacman

    if(mGhost->GetNextNode() == nullptr)
        return;
    auto comp = mGhost->GetNextNode()->GetComponent<AABBColliderComponent>();
    if(mGhost->GetComponent<AABBColliderComponent>()->Intersect(*comp)){
        mGhost->SetPosition(mGhost->GetNextNode()->GetPosition());
        mGhost->GetComponent<RigidBodyComponent>()->SetVelocity(Vector2(0,0));
        auto node = FindNextNode();
        if(node){
            mGhost->SetPreviousNode(mGhost->GetNextNode());
            mGhost->SetNextNode(node);
            UpdateDirection();
        }
    }
    mGhost->GetComponent<RigidBodyComponent>()->SetVelocity(mGhost->GetDirection()*mGhost->GetForwardSpeed());


}

void GhostState::UpdateDirection()
{
    // TODO [Parte 3.2]: https://ufv-inf216.lucasnferreira.com/p5-pacman
    auto newDirection = mGhost->GetNextNode()->GetPosition() - mGhost->GetPreviousNode()->GetPosition();
    newDirection.Normalize();
    if(mGhost->GetNextNode()->GetType() == PathNode::Type::Tunnel && mGhost->GetPreviousNode()->GetType() == PathNode::Type::Tunnel){
        newDirection *= -1;
    }
    mGhost->SetDirection(newDirection);

}

PathNode *GhostState::FindNearestNode(std::vector<PathNode*>& nodes, const Vector2& targetPosition, const std::set<PathNode::Type>* ignoreTypes, const std::set<PathNode *>* ignoreNodes)
{
    PathNode *nearestNode = nullptr;

    // TODO [Parte 3.3]: https://ufv-inf216.lucasnferreira.com/p5-pacman
    float min = FLT_MAX;
    for(auto i : nodes)
    {
        if(ignoreNodes->find(i) == ignoreNodes->end() && ignoreTypes->find(i->GetType()) == ignoreTypes->end())
        {
            float dist = (i->GetPosition() - targetPosition).LengthSq();
            if( min >= dist )
            {
                nearestNode = i;
                min = dist;
            }
        }
    }
    return nearestNode;
}


