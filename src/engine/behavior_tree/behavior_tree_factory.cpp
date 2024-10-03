#include "behavior_tree_factory.h"

static BehaviorTreeFactory* BehaviorTreeFactory::getFactory() {
    if (factory == nullptr) {
        factory = new BehaviorTreeFactory;
    }
    return factory;
}

void BehaviorTreeFactory::addNodeType(std::string type, BehaviorNode*(f*)()) {
    nodetypes.emplace(type, f);
}