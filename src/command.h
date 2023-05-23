#pragma once

enum CommandType {
	_CMD_NONE = 0, _CMD_TRANSITION, _CMD_STATE
};

struct Command {
	CommandType type;
	int value;
};