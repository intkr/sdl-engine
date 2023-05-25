#pragma once
#include <vector>
// intentionally included no delete pls ty :3
// I just want GitHub to see this file as c++
// so the language bar thing becomes 100% c++

enum CommandType {
	_CMD_NONE = 0, _CMD_TRANSITION, _CMD_STATE
};

struct Command {
	CommandType type;
	int value;
};