#pragma once

#include "behavior_node.h"

// Base node class for all types of control nodes.
class ControlNode : public BehaviorNode {
public:
    ControlNode() : currentNode(children.begin()) {}

    void reset() override;
    
protected:
    std::vector<BehaviorNode*>::iterator currentNode;
};

/* A sequence node processes its children in the given order.
If a child fails, the sequence returns failure.
If it succeeds, the sequence moves to the next child and repeats.
If all children returned success, the sequence returns success.
*/
class SequenceNode : public ControlNode {
public:
    NodeStatus process() override;
};

/* A fallback node processes its children in the given order.
If a child succeeds, the fallback returns success.
If it fails, the fallback moves to the next child and repeats.
If all children returned failure, the fallback returns failure.
*/
class FallbackNode : public ControlNode {
public:
    NodeStatus process() override;
};