#include "command.h"

Command::Command() : _type(_CMD_NONE), _value(0) {}

Command::Command(CommandType t, int v) : _type(t), _value(v) {}

void Command::operator=(const Command& c) {
	_type = c._type;
	_value = c._value;
}

void Command::setCommand(CommandType t, int v) {
	_type = t;
	_value = v;
}