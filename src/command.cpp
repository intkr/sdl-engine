#include "command.h"

Command::Command() : _type(_CMD_NONE), _value(0) {}

Command::Command(CommandType t, int v) : _type(t), _value(v) {}

CommandType Command::getType() {
	return _type;
}

int Command::getValue() {
	return _value;
}

void Command::setCommand(CommandType t, int v) {
	_type = t;
	_value = v;
}