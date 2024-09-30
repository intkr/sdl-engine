#include "sequence_node.h"

void ControlNode::reset() {
    for (BehaviorNode* child : children) {
        child->reset();
    }
    currentNode = children.begin();
}

void SequenceNode::process() {
    // if a sequence node has no children to process, return invalid
    if (children.size() == 0) return _NODE_INVALID;

    NodeStatus result = currentNode->process();
    switch (result) {
    case _NODE_FAILURE:
    case _NODE_RUNNING:
        return result;
        
    case _NODE_SUCCESS:
        currentNode++;
        if (currentNode == children.end()) return _NODE_SUCCESS;
        else return _NODE_RUNNING;
    
    case _NODE_INVALID:
        // assume invalid nodes as failures
    default:
        return _NODE_FAILURE;
    }
}

void FallbackNode::process() {
    // if a fallback node has no children to process, return invalid
    if (children.size() == 0) return _NODE_INVALID;

    NodeStatus result = currentNode->process();
    switch (result) {
    case _NODE_SUCCESS:
    case _NODE_RUNNING:
        return result;
        
    case _NODE_INVALID:
        // assume invalid nodes as failures and continue
    case _NODE_FAILURE:
        currentNode++;
        if (currentNode == children.end()) return _NODE_FAILURE;
        else return _NODE_RUNNING;
    
    default:
        return _NODE_FAILURE;
    }
}