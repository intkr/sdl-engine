#pragma once

#include "engine/behavior_tree/behavior_tree.h"

/* Component overview:

An entity's AI is separated into two sections - the 'objective generation' and 'behavior selection'.

1) Objective generation
    'Objectives' are things that an entity will try to accomplish.
    Based on information gathered from its surroundings, this section generates an objective.
    Generated objectives should be what an entity COULD do - it mustn't generate ones that it SHOULD but CANNOT do.

2) Behavior selection
    'Behaviors' are actions that an entity will perform for its objective.
    Each behavior will have a (dynamically calculated) priority value that affects the final action of an entity.
    Based on the given objective, this section selects the most appropriate behavior.

    Prior to selection, an entity may add, delete, or change behaviors in the list.

3) Behavior execution
    The details of a behavior is implemented as a behavior tree.

*/

class AIComponent {
public:
    // TODO: implement later
private:
    BehaviorTree aiTree;
};


/* random notes from https://www.youtube.com/watch?v=G5A0-_4dFLg and related vids

- The general logic is as follows:
    Information gathering - Decision making - Actuation / Execution

- Actions are simple programs with a specific duration, independent from AI (i.e. can be requested from any system).
  Action systems are used to register requests of specific actions.

  Actions must be fail-able - and its reasons should be available for debugging.
  Actions must not access any AI or logic-related systems - this allows test coverage.

    - (not from vid) These actions may be hardcoded, but in a way that can be applied to all types of entities.
      ex) 'Follow player' using player position and applying movements,
          'Shoot' using base entity functions,
          'PlayAnimation' using entity's command system, etc idk
      These actions should have a native cooldown system, and option parameters that affect the details of that action.


- There are two approaches to decision making - manager centric, and agent centric.

    - Manager Centric
        Consists of a global decision manager, and specific decision managers (idle / combat / etc).
        Global manager assigns a specific decision manager onto every agent based on internal logic.
    
    - Agent Centric
        Decision making and its performance is done by each agent themselves.
        The information used in decision making may be given by external systems.

*/