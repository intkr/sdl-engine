#include "command.h"

void Command::operator=(const Command& c) {
	_type = c._type;
	_value = c._value;
}

void Command::setCommand(CommandType t, int v) {
	_type = t;
	_value = v;
}