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

class RetryNode : public LogicNode {
public:
    // The initial process counts in the number of retries.
    // i.e. 1 means 'try once', 2 means 'try twice', and so on.
    RetryNode(int retries) : count(1), maxCount(retries) {}

    void reset() override;
    NodeStatus process() override;

private:
    int count;
    int maxCount;
}