#pragma once

enum CommandType {
	_CMD_NONE = 0, _CMD_TRANSITION, _CMD_STATE
};

class Command {
public:
	Command();
	Command(CommandType t, int v);
	void operator=(const Command& cmd);

	void setCommand(CommandType t, int v);
	CommandType getType() { return _type; }
	int getValue() { return _value; }
private:
	CommandType _type;
	int _value;
};