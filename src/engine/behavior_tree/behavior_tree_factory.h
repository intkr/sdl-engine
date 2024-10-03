#pragma once

// this looks messy ngl

class BehaviorTreeFactory {
public:
    static BehaviorTreeFactory* getFactory();
    void addNodeType(std::string type, BehaviorNode*(f*)());
    void createAITree(std::string filepath, std::map<std::string, BehaviorNode*>& nodes);

private:
    static BehaviorTreeFactory* factory;

    template<typename T>
    BehaviorNode* createNode() { return new T; }
    
    // value should be like "&createNode<type>"
    std::map<std::string, BehaviorNode*(*)()> nodetypes;
}