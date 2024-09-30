#include "behavior_node.h"

BehaviorNode::~BehaviorNode() {
    for (BehaviorNode* child : children) {
        delete child;
    }
}

void BehaviorNode::addChild(BehaviorNode* child) {
    children.push_back(child);
}