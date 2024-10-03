#include "ai_tree.h"

AITree::AITree(std::string filepath) {
    // use a factory and parse file to create ai tree
}

AITree::~AITree() {
    BehaviorNode* node;
    for (auto iter : subtrees) {
        node = iter.second;
        deleteNode(node);
    }
}

void AITree::deleteNode(BehaviorNode* node) {
    for (BehaviorNode* child : children) {
        deleteNode(child);
    }
    delete node;
}

void AITree::pushSubtree(std::string name) {
    try {
    BehaviorNode* node = subtrees.at(name);
    activeSubtrees.push(node);
    }
    catch (std::out_of_range& e) {
        // node with given name doesn't exist
    }
}