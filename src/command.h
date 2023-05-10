#pragma once

enum CommandType {
	_CMD_NONE = 0, _CMD_STATE
};

class Command {
public:
	Command();
	Command(CommandType t, int v);

	void setCommand(CommandType t, int v);
	CommandType getType();
	int getValue();
private:
	CommandType _type;
	int _value;
};