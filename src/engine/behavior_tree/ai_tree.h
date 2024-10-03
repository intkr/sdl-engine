#pragma once

#include <map>
#include <string>
#include <any>

#include "control_node.h"
#include "logic_node.h"
#include "action_node.h"

class AITree {
public:
    AITree();
    ~AITree();

    // might change to have some return value idk yet
    void update();
    void pushSubtree(std::string name);

    void setValue(std::string key, std::any value);
    std::any getValue(std::string key);

private:
    void deleteNode(BehaviorNode* node);
    // A collection of subtree roots with the subtree's name as the key.
    // Use this to access specific subtrees.
    std::map<std::string, BehaviorNode*> subtrees;
    // A stack of unfinished subtree roots.
    // This is used to return to the previously active subtree
    // after the current one has been fully processed.
    std::stack<BehaviorNode*> activeSubtrees;
    // A collection of user-defined values for internal usage.
    std::map<std::string, std::any> values;
};