#pragma once

#include "engine/behavior_tree/behavior_tree.h"

/* Component overview:

An AI component consists of a behavior tree (BT) and a finite-state machine (FSM).
A BT contains multiple trees - each representing some logic an object may follow.
Every update, the component calls the BT to process its current tree.
If a tree has been fully processed, the component checks the FSM to find out
which tree to process next.
*/

class AIComponent {
public:
    // TODO: implement later
private:
    BehaviorTree aiTree;
};