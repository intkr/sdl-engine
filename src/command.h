#pragma once

enum CommandType {
	_CMD_NONE = 0, _CMD_TRANSITION, _CMD_STATE
};

class Command {
public:
	Command() : _type(_CMD_NONE), _value(0) {}
	Command(CommandType t, int v) : _type(t), _value(v) {}
	void operator=(const Command& cmd);

	void setCommand(CommandType t, int v);
	CommandType getType() { return _type; }
	int getValue() { return _value; }
private:
	CommandType _type;
	int _value;
};