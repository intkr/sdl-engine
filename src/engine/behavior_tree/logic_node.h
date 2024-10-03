#pragma once

#include "behavior_node.h"

class LogicNode : public BehaviorNode {
public:
    // A logic node must have one child.
    // Any subsequent addition calls are ignored.
    void addChild(BehaviorNode* child) override;
};

class InverseNode : public LogicNode {
public:
    NodeStatus process() override;
}

class RepeatNode : public LogicNode {
public:
    // The initial process counts in the number of tries.
    // i.e. 1 means 'try once', 2 means 'try twice', and so on.
    RepeatNode(int tries) : count(1), maxCount(tries) {}

    void reset() override;
    NodeStatus process() override;

private:
    int count;
    int maxCount;
}