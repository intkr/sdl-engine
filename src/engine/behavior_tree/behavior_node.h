#pragma once
#include <vector>

enum class NodeStatus = { _NODE_INVALID = 0, _NODE_FAILURE, _NODE_SUCCESS, _NODE_RUNNING };

// Base node class for all types of behavior nodes.
class BehaviorNode {
public:
    ~BehaviorNode();

    virtual void addChild(BehaviorNode* child);
    virtual void reset() = 0;
    virtual NodeStatus process() = 0;

protected:
    std::vector<BehaviorNode*> children;
};