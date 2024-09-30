#pragma once

#include <map>
#include <string>

#include "control_node.h"
#include "logic_node.h"
#include "action_node.h"

// change name because this class contains multiple trees so 'tree' doesn't really fit here

class BehaviorTree {
public:

private:
    std::map<std::string, BehaviorNode*> roots;
};