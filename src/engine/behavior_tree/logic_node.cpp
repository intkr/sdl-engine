#include "logic_node.h"

void LogicNode::addChild(BehaviorNode* child) {
    if (children.size() > 0) return;
    children.push_back(node);
}

NodeStatus InverseNode::process() {
    if (children.size() == 0) return _NODE_INVALID;

    NodeStatus result = children[0]->process();
    switch (result) {
    case _NODE_INVALID:
    case _NODE_SUCCESS:
        return _NODE_FAILURE;

    case _NODE_FAILURE:
        return _NODE_SUCCESS;

    case _NODE_RUNNING:
    default:
        return result;
    }
}

void RepeatNode::reset() {
    count = 1;
}

NodeStatus RepeatNode::process() {
    if (children.size() == 0) return _NODE_INVALID;

    NodeStatus result = children[0]->process();
    switch (result) {
    case _NODE_INVALID:
        // assume invalid node as failure
    case _NODE_FAILURE:
        if (++count > maxCount) return _NODE_FAILURE;
        else children[0].reset();
    
    case _NODE_RUNNING:
        return _NODE_RUNNING;

    case _NODE_SUCCESS:
    default:
        return result;
    }
}